# Tasx - simple terminal todo manager

## Dependencies

1. [fmt](https://github.com/fmtlib/fmt)
2. [nlohmann::json](https://github.com/nlohmann/json)

## Installation

1. Clone repository

```shell
git clone https://github.com/mksbrsv/tasx && cd tasx
```

2. Make build directory

```shell
mkdir build && cd build
```

3. Build project

```shell
cmake .. && make
```

4. Run app

```shell
./tasx -h
```

## Tasks folder

All your tasks should be located in "HOME/.config/tasx/todos.json".
So, you should create this file:

```shell
mkdir -p ~/.config/tasx && touch ~/.config/tasx/todo.json
```

### File format

```json
[
  {
    "id": number,
    "priority": number,
    "status": boolean,
    "todo": string
  }
]
```
