# Maze

Руководство Maze.

1. [Установка](#Установка)
2. [Создание архива](#Создание_архива)
3. [Описание Maze](#Описание Maze)
4. [Удаление](#Удаление) 

## Установка

Для установки Maze перейдите в папку src и выполните в терминале:
> make instal

Дождитесь окончания установки. В папке src появится папка myapp_release, в которой располагается исполняемый файл.

## Создание архива

Чтобы создать архив программы, перейдите в папку src и выполните в терминале:
> make dist

Дождитесь окончания архивации. В папке src появится файл my_app.tar.gz.

## Описание Maze

- В программе предусмотрена кнопка для загрузки лабиринта из файла
- Максимальный размер лабиринта - 50х50 
- Загруженный лабиринт отрисован на экране в поле размером 500 x 500 пикселей 
- Толщина "стены" - 2 пикселя
- Имеется возможность автоматической генерации идеального лабиринта.
- Имеется возможность показать решение любого лабиринта, который сейчас изображен на экране

## Удаление

Для удаления Maze перейдите в папку src и выполните в терминале:
> make uninstal