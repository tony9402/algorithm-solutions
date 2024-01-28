import json


class SolutionData:
    def __init__(self):
        with open("solutions.json", "r") as f:
            self.data = json.load(f)
            f.close()

    def update_data(self, oj_name: str, pid: str, filename: str, hash_value: str, sequence: int):
        if oj_name not in self.data:
            self.data[oj_name] = {}

        if pid not in self.data[oj_name]:
            self.data[oj_name][pid] = {}

        if filename not in self.data[oj_name][pid]:
            self.data[oj_name][pid][filename] = {} 
        
        self.data[oj_name][pid][filename].update({
            "hash_value": hash_value,
            "sequence": sequence
        })

    def _exists(self, oj_name: str, pid: str, filename: str) -> bool:
        if oj_name not in self.data:
            return False

        if pid not in self.data[oj_name]:
            return False
        
        if filename not in self.data[oj_name][pid]:
            return False
        
        return True
        
    def get_sequence(self, oj_name: str, pid: str, filename: str) -> int:
        if not self._exists(oj_name=oj_name, pid=pid, filename=filename):
            return -1
        
        return self.data[oj_name][pid][filename]["sequence"]

    def check_uploaded_solution(self, oj_name: str, pid: str, filename: str, hash_value: str) -> bool:
        if not self._exists(oj_name=oj_name, pid=pid, filename=filename):
            return False

        return hash_value == self.data[oj_name][pid][filename].get("hash_value", "") 
    
    
    def save(self):
        with open("solutions.json", "w") as f:
            json.dump(self.data, f, indent=4, ensure_ascii=False)
            f.close()
