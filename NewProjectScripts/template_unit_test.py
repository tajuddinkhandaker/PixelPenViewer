#!/usr/bin/env python3
"""Template unit test helper for blank and nativeview projects."""

import shutil
import subprocess
import sys
from pathlib import Path

TEST_ROOT_DIRNAME = "temp_template_test"
BLANK_NAME = "TemplateBlankTest"
NATIVE_NAME = "TemplateNativeViewTest"


def run_bat(project_dir: Path, script_name: str) -> None:
    script_path = project_dir / script_name
    if not script_path.exists():
        raise FileNotFoundError(f"Batch script not found: {script_path}")

    print(f"Running {script_name} for {project_dir.name}...")
    result = subprocess.run(
        str(script_path),
        cwd=project_dir,
        shell=True,
        check=False,
    )
    if result.returncode != 0:
        raise RuntimeError(f"{script_name} failed for {project_dir.name} (exit {result.returncode})")


def create_project(template_class, project_name: str, output_root: Path) -> Path:
    print(f"Creating project '{project_name}' in {output_root}...")
    template = template_class(project_name, str(output_root))
    template.create()
    return output_root / project_name


def main() -> int:
    if sys.platform != "win32":
        print("This script is intended for Windows execution using .bat runners.")
        return 1

    script_root = Path(__file__).resolve().parent
    sys.path.insert(0, str(script_root.parent))
    from NewProjectScripts.create_project import BlankTemplate, NativeViewTemplate

    test_root = script_root / TEST_ROOT_DIRNAME

    if test_root.exists():
        print(f"Removing existing test root: {test_root}")
        shutil.rmtree(test_root)

    test_root.mkdir(parents=True, exist_ok=True)

    blank_dir = create_project(BlankTemplate, BLANK_NAME, test_root)
    native_dir = create_project(NativeViewTemplate, NATIVE_NAME, test_root)

    run_bat(blank_dir, "run_project.bat")
    run_bat(blank_dir, "fast_run_project.bat")

    run_bat(native_dir, "run_project.bat")
    run_bat(native_dir, "fast_run_project.bat")

    print("\nAll template create/build/run tests completed successfully.")
    print(f"Test artifacts are located under: {test_root}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
