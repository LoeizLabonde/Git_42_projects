#!/usr/bin/env bash
set -euo pipefail

PROJECT_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
PYTHON="${PYTHON:-python3}"
VENV_DIR="$PROJECT_DIR/.venv"

if ! command -v "$PYTHON" >/dev/null 2>&1; then
    printf 'Error: %s was not found.\n' "$PYTHON" >&2
    exit 1
fi

printf 'Using Python: %s\n' "$PYTHON"
if [[ -x "$VENV_DIR/bin/python" ]] && ! "$VENV_DIR/bin/python" -m pip --version >/dev/null 2>&1; then
    printf 'Existing virtual environment is incomplete; recreating it.\n'
    rm -rf "$VENV_DIR"
fi
if [[ ! -x "$VENV_DIR/bin/python" ]]; then
    "$PYTHON" -m venv "$VENV_DIR"
fi
"$VENV_DIR/bin/python" -m pip install -r "$PROJECT_DIR/requirements.txt"

if [[ "${BASH_SOURCE[0]}" != "$0" ]]; then
    source "$VENV_DIR/bin/activate"
    printf '\nSetup complete. Virtual environment activated.\n'
    printf 'Run: python %s/train.py\n' "$PROJECT_DIR"
else
    printf '\nSetup complete. Run:\n  %s/bin/python %s/train.py\n' "$VENV_DIR" "$PROJECT_DIR"
    printf 'Or activate it in your current shell with:\n  source %s/bin/activate\n' "$VENV_DIR"
fi
