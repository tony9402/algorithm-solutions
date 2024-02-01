import os
import argparse
import json
from subprocess import check_output as Cmd
from urllib import request

from utils import parse_metadata, EXTENSION_TO_LANGUAGE, OJ_NAMES


class WrongPRException(Exception):
    ...


def load_arg():
    parser = argparse.ArgumentParser()
    arg = parser.add_argument
    arg('--pr_number', type=int)
    arg('--url', type=str)
    return parser.parse_args()


def check_language(path: str) -> str:
    ext = os.path.splitext(path)[-1].lstrip('.')
    return EXTENSION_TO_LANGUAGE.get(ext, "404")


def check_oj_problem_number(path: str) -> str:
    return os.path.abspath(path).split('/')[-2]


def check_solution_path(path: str) -> bool:
    fullpath = os.path.abspath(path)
    words = fullpath.split("/")
    if len(words) < 4:
        return False
    
    flag = True
    flag &= words[-4] == "solutions"
    flag &= words[-3] in OJ_NAMES

    try:
        int(words[-2])
    except ValueError:
        flag = False
    
    flag &= "." in words[-1]

    return flag


def get_oj_name(path: str) -> str:
    fullpath = os.path.abspath(path)
    return fullpath.split("/")[-3]


def get_pr_file(
    pr_number: int
) -> str:
    Cmd(f"git fetch origin +refs/pull/{pr_number}/merge", shell=True).decode()
    files = Cmd(f"git --no-pager diff --name-only FETCH_HEAD $(git merge-base FETCH_HEAD main)", shell=True).decode()
    files = [file.strip() for file in files.split() if file.strip() != ""]
    return files


def check_solution_pr(
    file: str
) -> bool:
    return file.startswith('solutions')


def save_result(data: dict) -> None:
    ret = {}
    for key, value in data.items():
        ret[key] = str(value)
    
    with open("result.json", "w") as f:
        json.dump(ret, f)
        f.close()
    # for key, value in data.items():
    #     with open(key, "w") as f:
    #         f.write(str(value))
    #         f.close()


def main(
    args = load_arg(),
):
    pr_number = args.pr_number

    result = {
        "SOLUTION_PR": False,
        "SOLUTION_PER_PR": True,
        "METADATA": True,
        "SOLUTION_PATH": True,
        "SOLUTION_LANGUAGE": "404",
        "SOLUTION_AUTHOR": "",
        "SOLUTION_DESCRIPTION": "",
        "OJ_NAME": "",
        "OJ_PROBLEM_NUMBER": "",
        "OJ_URL": "",
    }

    files = get_pr_file(pr_number=pr_number)
    for file in files:
        if file.startswith("solutions"):
            result["SOLUTION_PR"] = True

    if len(files) > 1:
        result["SOLUTION_PER_PR"] = False
        save_result(result)
        exit(0)
    
    Cmd("git checkout FETCH_HEAD", shell=True)

    file = files[0]
    
    result["SOLUTION_PATH"] = check_solution_path(file)
    result["SOLUTION_LANGUAGE"] = check_language(file)
    result["OJ_NAME"] = get_oj_name(file)
    result["OJ_PROBLEM_NUMBER"] = check_oj_problem_number(file)

    try:
        with request.urlopen(f"{args.url}/problem/url?oj_name={result['OJ_NAME']}&oj_problem_number={result['OJ_PROBLEM_NUMBER']}") as req:
            url = req.read().decode('utf-8').replace('\\', '').replace('"', '')
            result["OJ_URL"] = url
    except:
        result["OJ_URL"] = ""

    with open(file, 'r') as f:
        code_lines = f.readlines()
        f.close()
    
    metadata = parse_metadata(code_lines)
    if len(metadata.keys()) != 3:
        result["METADATA"] = False
    else:
        result["SOLUTION_AUTHOR"] = metadata["Authored by"]

    start_index = -1
    for idx in range(len(code_lines) - 1, -1, -1):
        if 'Solution Description' in code_lines[idx]:
            start_index = idx
            break
    
    if start_index != -1:
        result["SOLUTION_DESCRIPTION"] = "".join(code_lines[start_index:])
    
    save_result(result)


if __name__ == "__main__":
    main()