# Tasx - simple terminal todo manager

## Usage

```
$ tasx -h

Usage: tasx [<options>...]

Options:
none           Show stats
--help, -h     Help menu
--list, -l     Display list of tasks
--done, -d     Mark task done
--new, -n      Create new task
--priority, -p Set priority [id] [priority{1-4}]
--go, -g       Mark task in process
--remove, -r   Remove task from list
--clear, -c    Clear list

Priority:
1. Low - white color
2. Medium - yellow color
3. High - red color
4. Critical - red bold color

Status:
1. Todo - [ ]
2. In process - [*]
3. Done - [x]
```

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

All your tasks should be located in **"HOME/.config/tasx/todos.json"**.
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
    "status": number,
    "todo": string
  }
]
```

## TODO

- [ ] Add windows support
