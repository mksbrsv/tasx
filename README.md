# Tasx - simple terminal todo manager

## Usage

```
$ tasx -h

Usage: tasx [<options>...]
Options:
  -help            Help menu
  none             Show stats
  -list [-hidden]  Display list of tasks, display with hidden done tasks
  -done            Mark task done: [@group_name] id
  -add [-group]    Create new task [@group_name], add new group [group_name]
  -pr              Set priority [@group_name] id priority{1-4}
  -do              Mark task in process [@group_name] id
  -edit            Edit task [@group_name] id subject
  -delete [-group] Remove task from list [@group_name] id, remove group [group_name]
  -clear           Clear list [@group_name]
Addition:
  If no group name provided, program will use default group - 'Board'
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
./tasx -help
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
    "name": string
    "list": [
      {
        "id": number,
        "priority": number,
        "status": number,
        "todo": string
      }
    ]
  }
]
```

## Inspiration

[taskbook](https://github.com/klaussinani/taskbook)

## TODO

- [ ] Add windows support
- [x] Add groups
