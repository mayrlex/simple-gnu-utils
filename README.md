# simple-gnu-utils
Minimal implementation of GNU cat and grep utilities

## Build

### Common

Собирает и cat и grep

```bash
make
```
### cat

Отдельно собирает cat

```bash
make cat
```
### grep

Отдельно собирает cat

```bash
make grep
```

### Rebuild

Пересобирает весь проект

```bash
make r
```

## Test

### Unit-тестирование

Для cat:

```bash
make test_cat
```

Для grep:

```bash
make test_grep
```

### Clang

Проверка на соответствие стилям:

```bash
make clang_check
```

Автоматическое исправление стиля кода:

```bash
make clang
```



## Clean

Чистит проект от лишнего мусора (Объектные файлы, артефакты)

```bash
make с
```