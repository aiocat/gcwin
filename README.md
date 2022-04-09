# GcWin
Global command manager for Windows

## Download
Download gcwin from [here](https://github.com/aiocat/gcwin/releases/latest)

## Setup
- Add executable to PATH.
- Create `gcwin` file in `Appdata/Local`

## Usage
Example `gcwin` file:
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

Now you are avaible to use commands with `gcwin <command name>`
- `gcwin svelte`
- `gcwin echo`

## License
GcWin is distributed under MIT license. for more information:
- https://raw.githubusercontent.com/aiocat/gcwin/main/LICENSE