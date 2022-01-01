# Tasx - simple terminal todo manager

## Usage

```
$ tasx -h

Usage: tasx [<options>...]

Options:
--help, -h     Help menu
none           Show stats
list           Display list of tasks
hidden         Display list with hidden done tasks
done           Mark task done
add            Create new task
pr             Set priority [id] [priority{1-4}]
do             Mark task in process
edit           Edit task [id] [subject]
delete         Remove task from list
clear          Clear list

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
- [ ] Add dates for tasks
- [ ] Add groups
