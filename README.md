# GcWin
Global command manager for Windows

## Download
Download gcwin from [here](https://github.com/aiocat/gcwin/releases/latest)
- **Current Version**: `v1.2.0`

## Setup
- Add executable to PATH.
- Run `gcwin init` command.

## Usage
Example `gcwin` file: (you can open the file in notepad with `gcwin edit` command.)
```sh
echo:
color f0
cls
echo Hello World!

svelte:
npx degit sveltejs/template
npm install
npm run dev
```

Now you are avaible to use commands with `gcwin run <command name>`
- `gcwin run svelte`
- `gcwin run echo`

## License
GcWin is distributed under MIT license. for more information:
- https://raw.githubusercontent.com/aiocat/gcwin/main/LICENSE