Применим алгоритм к нашему сервису:

1.  Начальные состояния:
    *    Database: 0
    *    UserService: 1 (от `Database`)
    *    ProductService: 1 (от `Database`)
    *    OrderService: 2 (от `UserService`, `ProductService`)
    *    Frontend: 3 (от `UserService`, `ProductService`, `OrderService`)
2.  Очередь: [Database] (единственная вершина со степенью 0).
3.  Шаг 1:
    *   Берем `Database`. Итоговый список: [`Database`].
    *   Уменьшаем степени `UserService` (1-1=0) и `ProductService` (1-1=0).
    *   Добавляем `UserService` и `ProductService` в очередь. Очередь: [`UserService`, `ProductService`].
4.  Шаг 2:
    *   Берем `UserService`. Итоговый список: [`Database`, `UserService`].
    *   Уменьшаем степени `OrderService` (2-1=1) и `Frontend` (3-1=2).
    *   Ничья степень не стала 0. Очередь: [`ProductService`].
5.  Шаг 3:
    *   Берем `ProductService`. Итоговый список: [`Database`, `UserService`, `ProductService`].
    *   Уменьшаем степени `OrderService` (1-1=0) и `Frontend` (2-1=1).
    *   Добавляем `OrderService` в очередь (степень стала 0). Очередь: [`OrderService`].
6.  Шаг 4:
    *   Берем `OrderService`. Итоговый список: [`Database`, `UserService`, `ProductService`, `OrderService`].
    *   Уменьшаем степень `Frontend` (1-1=0).
    *   Добавляем `Frontend` в очередь. Очередь: [`Frontend`].
7.  Шаг 5:
    *   Берем `Frontend`. Итоговый список: [`Database`, `UserService`, `ProductService`, `OrderService`, `Frontend`].
    *   Зависимых вершин нет. Очередь пуста.
8.  Алгоритм завершен. Список содержит все вершины.

Полученная последовательность `Database`, `UserService`, `ProductService`, `OrderService`, `Frontend` является корректным порядком развертывания. (Заметим, что если бы на шаге 2 мы сначала взяли `ProductService`, итоговый порядок мог бы быть другим, но все равно оставался корректным).
