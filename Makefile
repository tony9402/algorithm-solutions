PYTHON ?= $(if $(wildcard .venv/bin/python),.venv/bin/python,python3)
BASE_REF ?= origin/main

.PHONY: help precheck checkall

help:
	@echo "make precheck                 전체 솔루션 형식만 점검"
	@echo "make checkall                 형식·테스트·Pages 빌드 전체 점검"
	@echo "make precheck BASE_REF=main   비교 기준 ref 변경"

precheck:
	@$(PYTHON) scripts/precheck.py --base-ref "$(BASE_REF)"

checkall:
	@$(PYTHON) scripts/precheck.py --base-ref "$(BASE_REF)" --all
