all:
	gcc -o uart_tx uart_tx.c
tx:
	gcc -o uart_tx uart_tx.c
rx:
	gcc -o uart_rx uart_rx.c
main:
	gcc -o uart main.c
