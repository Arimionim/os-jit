#  Кусочек JIT компилятора

## Программа может
 * Выделить память с помощью mmap(2).
 * Записать в выделенную память машинный код, соответсвующий какой-либо функции.
 * Изменить права на выделенную память - чтение и исполнение. See: mprotect(2).
 * Вызвать функцию по указателю на выделенную память.
 * Освободить выделенную память.
