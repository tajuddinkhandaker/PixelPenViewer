#!/usr/bin/env python3
"""
Create project module inside NewProjectScripts package.
"""

import argparse
import sys
from pathlib import Path

PLACEHOLDER_PROJECT_NAME = "{{PROJECT_NAME}}"


def read_text(path: Path) -> str:
    return path.read_text(encoding='utf-8')


def write_text(path: Path, data: str) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(data, encoding='utf-8')


class ProjectTemplate:
    def __init__(self, project_name: str, output_dir: str, template_name: str):
        self.project_name = project_name
        self.output_dir = Path(output_dir).resolve()
        self.project_root = self.output_dir / project_name
        # templates live inside the package in 'template_files'
        self.templates_root = Path(__file__).resolve().parent / 'template_files'
        self.template_dir = self.templates_root / template_name
        self.validate_template_dir()

    def validate_template_dir(self) -> None:
        if not self.template_dir.exists() or not self.template_dir.is_dir():
            raise FileNotFoundError(f"Template folder not found: {self.template_dir}")

    def create_directory_structure(self) -> None:
        for directory in [
            self.project_root / 'src',
            self.project_root / 'include',
            self.project_root / 'res',
        ]:
            directory.mkdir(parents=True, exist_ok=True)

    def render_template(self, content: str) -> str:
        return content.replace(PLACEHOLDER_PROJECT_NAME, self.project_name)

    def copy_template_tree(self) -> None:
        self.create_directory_structure()
        for source_file in sorted(self.template_dir.rglob('*')):
            if source_file.is_dir():
                continue
            rel = source_file.relative_to(self.template_dir)
            destination = self.project_root / rel
            destination.parent.mkdir(parents=True, exist_ok=True)
            text = read_text(source_file)
            text = self.render_template(text)
            write_text(destination, text)
            print(f"  Created: {destination.relative_to(self.project_root).as_posix()}")

    def create(self) -> None:
        raise NotImplementedError


class BlankTemplate(ProjectTemplate):
    def __init__(self, project_name: str, output_dir: str):
        super().__init__(project_name, output_dir, 'blank')

    def create(self) -> None:
        self.copy_template_tree()
        print(f"\n✓ Blank project '{self.project_name}' created at {self.project_root}")


class NativeViewTemplate(ProjectTemplate):
    def __init__(self, project_name: str, output_dir: str):
        super().__init__(project_name, output_dir, 'nativeview')

    def create(self) -> None:
        self.copy_template_tree()
        print(f"\n✓ NativeView project '{self.project_name}' created at {self.project_root}")


def main() -> None:
    parser = argparse.ArgumentParser(
        description='OpenGL/GLFW Project Scaffolding Tool',
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog='''
Examples:
  python -m NewProjectScripts MyProject --mode blank
  python -m NewProjectScripts MyApp --mode nativeview -o C:\\Projects
''',
    )

    parser.add_argument('project_name', help='Name of the project to create')
    parser.add_argument('-m', '--mode', choices=['blank', 'nativeview'], default='blank', help='Project template mode (default: blank)')
    parser.add_argument('-o', '--output', default='.', help='Output directory for the project (default: current directory)')

    args = parser.parse_args()

    print(f"Creating {args.mode} project '{args.project_name}'...\n")

    try:
        if args.mode == 'blank':
            template = BlankTemplate(args.project_name, args.output)
        else:
            template = NativeViewTemplate(args.project_name, args.output)

        template.create()
        print('\nProject created successfully!')
        print('Next steps:')
        print(f'  cd {template.project_root}')
        print('  mkdir build && cd build')
        print('  cmake ..')
        print('  cmake --build .')
    except Exception as exc:
        print(f'Error: {exc}', file=sys.stderr)
        sys.exit(1)


if __name__ == '__main__':
    main()
