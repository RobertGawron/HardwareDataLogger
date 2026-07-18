# IntegrationTest doesnt work anyway
# targets := "FirmwarePCSimulator IntegrationTest"

targets := "FirmwarePCSimulator"
report_dir := "reports"

prepare-report-dir:
    mkdir -p {{report_dir}}

# ============================================================
# Formatting
# ============================================================

format targets=targets:
    black {{targets}}
    ruff check {{targets}} --fix

check-format targets=targets:
    black --check {{targets}}

# ============================================================
# Strict Linting
# ============================================================

lint targets=targets:
    ruff check {{targets}}
    mypy {{targets}}

# ============================================================
# Security
# ============================================================

security targets=targets:
    bandit -r {{targets}}

dependency-security:
    pip-audit --strict

supply-chain:
    safety check --full-report

# ============================================================
# SBOM
# ============================================================

sbom: prepare-report-dir
    cyclonedx-py -o {{report_dir}}/sbom.json

# ============================================================
# Complexity
# ============================================================

complexity-gate targets=targets:
    radon cc {{targets}} -a -nc
    radon mi {{targets}} -nb

# ============================================================
# Reports
# ============================================================

report targets=targets: prepare-report-dir
    ruff check {{targets}} --output-format=json > {{report_dir}}/ruff.json || true
    mypy {{targets}} > {{report_dir}}/mypy.txt || true
    mypy --html-report {{report_dir}}/mypy-html {{targets}} || true
    radon cc {{targets}} -j > {{report_dir}}/radon-cc.json || true
    radon mi {{targets}} -j > {{report_dir}}/radon-mi.json || true
    bandit -r {{targets}} -f html -o {{report_dir}}/bandit.html || true
    pip-audit -f json > {{report_dir}}/pip-audit.json || true
    safety check --json > {{report_dir}}/safety.json || true
    cyclonedx-py -o {{report_dir}}/sbom.json || true

# ============================================================
# HARD CI GATE
# ============================================================

ci targets=targets:
    just check-format targets="{{targets}}"
    just lint targets="{{targets}}"
    just security targets="{{targets}}"
    just dependency-security
    just supply-chain
    just complexity-gate targets="{{targets}}"