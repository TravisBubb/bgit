# BGit

The intent of this project is to create a command-line tool with a simplified feature-set of git. The following are the targeted features for implementation:
- init
    - initialize a new repository and create any files required
    - .bgitignore - specify filename patterns to ignore changes for
- commits
    - commit changes
    - track what changes have been made since last commit (new files, deleted files, modified files)
    - view commit history
    - checkout old commits
    - revert changes (create a new commit that updates the branch to a previous commit as specified in the command)
- branches
    - be able to create a new branch
    - create a 'root' branch when repository is initialized


Wishlist Features:
- allow cloning remote git repos (e.g., GitHub)
    - convert from git -> bgit repo
- allow pushing to GitHub
- allow pulling from GitHub

- allow initializing repositories with specific boiler-plate for different projects (e.g., dotnet web api)

