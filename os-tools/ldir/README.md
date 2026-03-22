# ldir

A lightweight tree-like directory listing tool for Linux/macOS.

## Install as a Bash Command

1. Save the script to `~/bin`:
```bash
	mkdir -p ~/bin cp ldir ~/bin
```

2. Make it executable:
```bash
	chmod +x ~/bin/list_files
```

3. Add ~/bin to your PATH (if it’s not already):
```bash
	bash export PATH="$HOME/bin:$PATH" >
```

4. Reload your shell:
```bash
	source ~/.bashrc   # or ~/.zshrc or ~/.bash_profile
```


## Usage Examples

```bash
ldir
```
	Lists the current folder with full depth.

```bash
ldir -L 3
```
	Lists the current folder up to depth 3.

```bash
ldir my_folder
```
	Lists a specific folder with full depth.

```bash
ldir my_folder 2
```
	Lists a specific folder up to depth 2.


## Optional Flags
* `-L <level>` — Max display depth (like `tree -L`)
* `--no-color` — Disable colored output
* `-d, --dirs-only` — Show directories only
* `--help` — Show help message

