import shutil, subprocess
from pathlib import Path

# Helper script to add GameAPI submodules for any mod folders that don't have one, then update all submodules to latest commit
# Fun fact: I HATE WORKING WITH GIT SUBMODULES!!!!

def main():
    for mod in Path.cwd().glob('*'):
        if not mod.is_dir() or mod.name == ".git":
            continue

        gameapi = Path(mod / "GameAPI")
        if not gameapi.is_dir():
            if gameapi.is_file():
                gameapi.unlink()
            add_command = subprocess.run(["git", "submodule", "add", "https://github.com/RSDKModding/RSDKv5-GameAPI", Path(mod.name, "GameAPI")])

    update_command = subprocess.run(["git", "submodule", "update", "--remote", "--init"])

if __name__ == '__main__':
    main()
