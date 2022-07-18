#include "../include/minishell.h"

#define R "\x1B[31m"
#define W "\x1B[37m"
#define Y "\x1B[33m"
#define G "\x1B[32m"
#define N "\x1B[0m"
#define M "\x1B[35m"
#define C "\x1B[36m"
#define O_C "\033[46m"
#define O_R "\033[41m"

void	invalid_argv(void)
{
	printf("⠀⠀⠀⠀%s⢰⣾⠾⠶⠷⠶⣶⣄⠀⠀⢰⣾⠶⠷⠶⠾⠶⣶⡄⠀⠀⣶⣶⠀⠀⠀⠀⠀⣶⡇⠀⠀⣶⡆⠀⠀⠀⠀⢐⣶⡇\n", R);
	printf("⠀⠀⠀⠀⢸⣿⠀⠀⠀⠀⢘⣿⠅⠀⢸⣿⠀⠀⠀⠀⠀⢸⣿⠀⠀⣿⣿⠀⠀⠀⠀⠀⣾⡇⠀⠀⣿⡇⠀⠀⠀⠀⢈⣿⡇\n");
	printf("⠀⠀⠀⠀⢸⣿⣆⣰⣀⣶⣾⠏⠀⠀⢸⣿⣀⣀⣀⣀⣀⣾⠏⠀⠀⣿⣿⠀⠀⠀⠀⠀⣾⡇⠀⠀⣿⣇⣶⣶⣶⣶⣾⣿⡇\n");
	printf("⠀⠀⠀⠀⢸⣿⠉⠉⠉⠉⠙⣿⡆⠀⢸⣿⠛⠛⠛⠛⠛⣿⣆⠀⠀⣿⣿⠀⠀⠀⠀⠀⣾⡇⠀⠀⣿⡏⠉⠉⠉⠉⠩⣿⡇\n");
	printf("⠀⠀⠀⠀⢸⣿⠀⠀⠀⠀⢀⣾⡇⠀⢸⣿⠀⠀⠀⠀⠀⢸⣿⠀⠀⠸⣿⡀⠀⠀⠀⢠⣿⠇⠀⠀⣿⡇⠀⠀⠀⠀⠰⣿⡇\n");
	printf("⠀⠀⠀⠀⠸⠿⠿⠿⠿⠿⠟⠋⠀⠀⠸⠿⠀⠀⠀⠀⠀⠸⠿⠄⠀⠀⠙⠿⠶⠶⠾⠟⠋⠀⠀⠀⠿⠇⠀⠀⠀⠀⠈⠿⠇%s\n\n", N);
	printf("%s⠀⠀⠀⠀⢀⣀⣀⣀⡀⠀⢀⣀⣀⡀⡀⠀⡀⠀⣀⣀⣀⣀⣀⠀⠀⠀⠀⢀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡀⠀⡀\n", Y);
	printf("⠀⠀⠀⠀⠿⠿⠿⠿⣿⣿⡿⠿⠿⠿⠇⠀⣿⣿⠿⠿⠿⠿⠿⢿⣿⣦⡀⠀⢻⣿⣦⠀⠀⠀⠀⠀⣼⣿⡟⠀\n");
	printf("⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⡇⠀⠀⠀⠀⠀⣿⣿⠀⠀⠀⠀⠀⠀⢹⣿⡇⠀⠀⠹⣿⣧⡀⠀⢀⣼⣿⠏⠀⠀\n");
	printf("⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⡇⠀⠀⠀⠀⠀⣿⣿⢀⣀⣀⣀⣀⣀⣾⣿⠃⠀⠀⠀⠘⣿⣷⣐⣾⣿⠃⠀⠀⠀\n");
	printf("⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⡇⠀⠀⠀⠀⠀⣿⣿⠿⠿⠿⠿⠿⢿⣿⣧⠀⠀⠀⠀⠀⠈⢿⣿⡿⠁⠀⠀⠀⠀\n");
	printf("⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⡇⠀⠀⠀⠀⠀⣿⣿⠀⠀⠀⠀⠀⠀⢻⣿⡆⠀⠀⠀⠀⠀⢸⣿⡇⠀⠀⠀⠀⠀\n");
	printf("⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⡇⠀⠀⠀⠀⠀⣿⣿⠀⠀⠀⠀⠀⠀⢸⣿⡇⠀⠀⠀⠀⠀⢸⣿⡇⠀⠀⠀⠀⠀\n");
	printf("⠀⠀⠀⠀⠀⠀⠀⠀⠛⠛⠃⠀⠀⠀⠀⠀⠛⠛⠀⠀⠀⠀⠀⠀⠘⠛⠛⠀⠀⠀⠀⠀⠘⠛⠃⠀⠀\n\n");
	printf("⠀⠀⠀⠀⣠⣤⠀⠀⠀⠀⠀⠀⠀⣀⣤⣤⣤⣄⡀⠀⠀⠀⠀⠀⠀⢀⣤⣄⠀⠀⠀⠀⠀⣠⡄⠀⠀⣤⣤⠀⠀⠀⠀⠀⣤⣄\n");
	printf("⠀⠀⠀⣰⣿⣿⣇⠀⠀⠀⠀⢠⣾⡿⠋⠉⠉⠛⢿⣧⡀⠀⠀⠀⠀⣼⡿⣿⡄⠀⠀⠀⠀⣿⡇⠀⠀⣿⣿⣧⡀⠀⠀⠀⣿⣿\n");
	printf("⠀⠀⢠⣿⠏⢹⣿⡄⠀⠀⢠⣿⡏⠀⠀⠀⠀⠀⠈⠛⠃⠀⠀⠀⣰⣿⠃⢿⣿⡀⠀⠀⠀⣿⡇⠀⠀⣿⡟⢻⣷⡄⠀⠀⣿⣿\n");
	printf("⠀⠀⣾⡟⠀⠀⣿⣿⠀⠀⢸⣿⡇⠀⠀⢰⣶⣶⣶⣶⣶⠀⠀⢠⣿⠏⠀⠈⣿⣧⠀⠀⠀⣿⡇⠀⠀⣿⡇⠀⠻⣿⣄⠀⣿⣿\n");
	printf("⠀⣼⣿⠿⠿⠿⠿⣿⣧⠀⠸⣿⣇⠀⠀⠀⠀⠀⢀⣿⣿⠀⠀⣾⡿⠿⠿⠿⠿⣿⡆⠀⠀⣿⡇⠀⠀⣿⡇⠀⠀⠹⣿⣆⣿⣿\n");
	printf("⢰⣿⠇⠀⠀⠀⠀⢹⣿⡆⠀⠹⣿⣦⣄⣀⣀⣠⣾⢿⣿⠀⣼⣿⠁⠀⠀⠀⠀⢿⣿⡄⠀⣿⡇⠀⠀⣿⡇⠀⠀⠀⠘⣿⣿⣿\n");
	printf("⠛⠋⠀⠀⠀⠀⠀⠀⠛⠛⠀⠀⠈⠙⠛⠛⠛⠋⠁⠘⠋⠀⠛⠋⠀⠀⠀⠀⠀⠈⠛⠃⠀⠙⠋⠀⠀⠛⠃⠀⠀⠀⠀⠈⠛⠋%s\n\n", N);
}

void	welcome(void)
{
	printf("%sWelcome to Yet Another MiniShell Project v. 1.6", O_C);
	printf(" (YAMSP)!%s\n", N);
	printf("%sIt is as beautiful as a shell 🐚 and has two", O_C);
	printf(" extra modes.%s\n", N);
	printf("%sFeel free to explore our code and find how to", O_C);
	printf(" activate them!%s\n", N);
	printf("%sRemember:%s\n\n", O_C, N);
	printf("%s⢠⣴⣶⣦⣤⣄⠀⠀⣦⣶⣶⣶⣶⡆⠀⠀⠀⠀⢀⣤⣶⣶⣦⣄⠀⠀⣲⣴⣶⣶⣦⣦⠀⣴⣤⡀⠀⠀", C);
	printf("⢠⡄⢰⣶⣶⣶⣶⣴⣤⢠⣤⠀⠀⠀⠀⢠⣦⣶⣶⣦⣶⡆\n");
	printf("⢸⣿⠀⠀⠈⣿⠇⠀⣿⠀⠀⠀⠀⠀⠀⠀⠀⢠⣾⠏⠀⠀⠈⠻⠧⠀⢻⡇⠀⠀⠀⠀⠀⣿⡿⣷⡀⠀⢸⡇");
	printf("⠀⠀⠀⣿⡇⠀⠀⢸⣿⠀⠀⠀⠀⢸⣿⠀⠀⠀⠀⠀\n");
	printf("⢸⣿⠾⠿⠿⣿⡀⠀⣿⠷⠶⠶⠶⠂⠀⠀⠀⢸⣿⠀⠀⠶⠶⢶⣦⠀⢸⡷⠶⠶⠶⠶⠀⣿⡇⠘⣿⡄⢸⡇");
	printf("⠀⠀⠀⣿⡇⠀⠀⢸⣿⠀⠀⠀⠀⢸⣿⠶⠶⠶⠶⠆\n");
	printf("⢸⣿⠀⠀⠀⣼⡿⠀⣿⠀⠀⠀⠀⠀⠀⠀⠀⠘⣿⣄⠀⠀⢀⣼⣿⠀⢸⡇⠀⠀⠀⠀⠀⣿⡇⠀⠈⢿⣾⡇");
	printf("⠀⠀⠀⣿⡇⠀⠀⢸⣿⠀⠀⠀⠀⢸⣿⠀⠀⠀⠀⠀\n");
	printf("⠘⠿⠿⠿⠟⠛⠁⠀⠿⠿⠿⠿⠿⠟⠀⠀⠀⠀⠈⠻⠿⠿⠟⠋⠟⠀⠹⠿⠿⠿⠿⠿⠀⠻⠇⠀⠀⠈⠻⠇");
	printf("⠀⠀⠀⠿⠇⠀⠀⠘⠿⠿⠿⠿⠿⠘⠿⠿⠿⠿⠿⠇%s\n\n\n", N);
}

void	secret_mode(void)
{
	printf("%s______________________________________________", O_R);
	printf("________________%s\n", N);
	printf("%s______________________________________________", O_R);
	printf("________________%s\n", N);
	printf("%s░░░░░░░░░░░░░░░░░░░░░░█████████\n", Y);
	printf("%s░░███████░░░░░░░░░░███▒▒▒▒▒▒▒▒███\n", Y);
	printf("%s░░█▒▒▒▒▒▒█░░░░░░░███▒▒▒▒▒▒▒▒▒▒▒▒▒███\n", Y);
	printf("%s░░░█▒▒▒▒▒▒█░░░░██▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒██\n", Y);
	printf("%s░░░░█▒▒▒▒▒█░░░██▒▒▒▒▒%s██%s▒▒▒▒▒▒%s██%s▒▒▒▒▒███\n", Y, R, Y, R, Y);
	printf("%s░░░░░█▒▒▒█░░░█▒▒▒▒▒▒%s████%s▒▒▒▒%s████", Y, R, Y, R);
	printf("%s▒▒▒▒▒▒██\n", Y);
	printf("%s░░░█████████████▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒██\n", Y);
	printf("%s░░░█▒▒▒▒▒▒▒▒▒▒▒▒█▒▒▒▒▒▒▒▒▒█▒▒▒▒▒▒▒▒▒▒▒██\n", Y);
	printf("%s░██▒▒▒▒▒▒▒▒▒▒▒▒▒█▒▒▒██▒▒▒▒▒▒▒▒▒▒██▒▒▒▒██\n", Y);
	printf("%s██▒▒▒███████████▒▒▒▒▒██▒▒▒▒▒▒▒▒██▒▒▒▒▒██\n", Y);
	printf("%s█▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒█▒▒▒▒▒▒████████▒▒▒▒▒▒▒██\n", Y);
	printf("%s██▒▒▒▒▒▒▒▒▒▒▒▒▒▒█▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒██\n", Y);
	printf("%s░█▒▒▒███████████▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒██\n", Y);
	printf("%s░██▒▒▒▒▒▒▒▒▒▒████▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒█\n", Y);
	printf("%s░░████████████░░░█████████████████\n", Y);
	printf("%s______________________________________________", O_R);
	printf("________________%s\n", N);
	printf("%s______________________________________________", O_R);
	printf("________________%s\n", N);
	printf("%s\nSecret mode has been activated!\n\n", C);
}

void	uwu_mode(void)
{
	printf("%sUwU\n", M);
	printf("⡆⣐⢕⢕⢕⢕⢕⢕⢕⢕⠅⢗⢕⢕⢕⢕⢕⢕⢕⠕⠕⢕⢕⢕⢕⢕⢕⢕⢕⢕\n");
	printf("⢐⢕⢕⢕⢕⢕⣕⢕⢕⠕⠁⢕⢕⢕⢕⢕⢕⢕⢕⠅⡄⢕⢕⢕⢕⢕⢕⢕⢕⢕\n");
	printf("⢕⢕⢕⢕⢕⠅⢗⢕⠕⣠⠄⣗⢕⢕⠕⢕⢕⢕⠕⢠⣿⠐⢕⢕⢕⠑⢕⢕⠵⢕\n");
	printf("⢕⢕⢕⢕⠁⢜⠕⢁⣴⣿⡇⢓⢕⢵⢐⢕⢕⠕⢁⣾⢿⣧⠑⢕⢕⠄⢑⢕⠅⢕\n");
	printf("⢕⢕⠵⢁⠔⢁⣤⣤⣶⣶⣶⡐⣕⢽⠐⢕⠕⣡⣾⣶⣶⣶⣤⡁⢓⢕⠄⢑⢅⢑\n");
	printf("⠍⣧⠄⣶⣾⣿⣿⣿⣿⣿⣿⣷⣔⢕⢄⢡⣾⣿⣿⣿⣿⣿⣿⣿⣦⡑⢕⢤⠱⢐\n");
	printf("⢠⢕⠅⣾⣿⠋⢿⣿⣿⣿⠉⣿⣿⣷⣦⣶⣽⣿⣿⠈⣿⣿⣿⣿⠏⢹⣷⣷⡅⢐\n");
	printf("⣔⢕⢥⢻⣿⡀⠈⠛⠛⠁⢠⣿⣿⣿⣿⣿⣿⣿⣿⡀⠈⠛⠛⠁⠄⣼⣿⣿⡇⢔\n");
	printf("⢕⢕⢽⢸⢟⢟⢖⢖⢤⣶⡟⢻⣿⡿⠻⣿⣿⡟⢀⣿⣦⢤⢤⢔⢞⢿⢿⣿⠁⢕\n");
	printf("⢕⢕⠅⣐⢕⢕⢕⢕⢕⣿⣿⡄⠛⢀⣦⠈⠛⢁⣼⣿⢗⢕⢕⢕⢕⢕⢕⡏⣘⢕\n");
	printf("⢕⢕⠅⢓⣕⣕⣕⣕⣵⣿⣿⣿⣾⣿⣿⣿⣿⣿⣿⣿⣷⣕⢕⢕⢕⢕⡵⢀⢕⢕\n");
	printf("⢑⢕⠃⡈⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢃⢕⢕⢕\n");
	printf("⣆⢕⠄⢱⣄⠛⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠿⢁⢕⢕⠕⢁\n");
	printf("⣿⣦⡀⣿⣿⣷⣶⣬⣍⣛⣛⣛⡛⠿⠿⠿⠛⠛⢛⣛⣉⣭⣤⣂⢜⠕⢑⣡⣴⣿\n");
	printf("⠀⠀⠀⣿⣿⡆⠀⠀⢸⣷⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⡇⠀⠀⣾⣿⡆⠀\n");
	printf("⠀⠀⠀⣿⣿⡇⠀⠀⢸⣿⢰⣿⡆⠀⣾⣿⡆⠀⣾⣷ ⣿⣿⡇⠀⠀⣿⣿⡇⠀\n");
	printf("⠀⠀⠀⣿⣿⡇⠀⠀⢸⣿⠘⣿⣿⣤⣿⣿⣿⣤⣿⡇⢻⣿⡇⠀⠀⣿⣿⡇⠀\n");
	printf("⠀⠀⠀⣿⣿⡇⠀⠀⢸⡿⠀⢹⣿⣿⣿⣿⣿⣿⣿⠁⢸⣿⣇⠀⢀⣿⣿⠇⠀\n");
	printf("⠀⠀⠀⠙⢿⣷⣶⣶⡿⠁⠀⠈⣿⣿⠟⠀⣿⣿⠇⠀⠈⠻⣿⣶⣾⡿⠋⠀\n");
}

void	normal_mode(void)
{
	printf("%s⢀⣀⡀⠀⠀⠀⣀⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⣀⡀\n", N);
	printf("⢸⣿⣿⣆⠀⠀⣿⣿⠀⠀⠀⣀⣀⣀⡀⠀⠀⠀⣀⡀⢀⣀⠀⢀⣀⠀⣀⣀⡀⢀⣀⣀⡀⠀⠀⠀⢀⣀⣀⡀⣀⣀⠀⢸⣿⡇\n");
	printf("⢸⣿⣿⣿⣧⡀⣿⣿⠀⢠⣾⣿⠟⠻⣿⣷⡀⠀⣿⣷⠿⠿⠀⣻⣿⡿⠻⣿⣿⡿⠟⢿⣿⡆⠀⣼⣿⠿⠛⢿⣿⣿⠀⢸⣿⡇\n");
	printf("⢸⣿⡇⠙⣿⣿⣿⣿⠀⢸⣿⡇⠀⠀⢸⣿⡇⠀⣿⣿⠀⠀⠀⣹⣿⠁⠀⢸⣿⡇⠀⢸⣿⡇⢸⣿⣏⠀⠀⠀⣿⣿⠀⢸⣿⡇\n");
	printf("⢸⣿⡇⠀⠈⢻⣿⣿⠀⠈⢿⣿⣦⣶⣿⡿⠃⠀⣿⣿⠀⠀⠀⣼⣿⠀⠀⢸⣿⡇⠀⢸⣿⡇⠀⢻⣿⣶⣦⣾⣿⣿⠀⢸⣿⡇\n");
	printf("⠈⠉⠁⠀⠀⠀⠉⠉⠀⠀⠀⠉⠉⠉⠉⠀⠀⠀⠉⠉⠀⠀⠀⠈⠉⠀⠀⠈⠉⠁⠀⠈⠉⠁⠀⠀⠈⠉⠉⠁⠉⠉⠀⠈⠉⠁\n");
	printf("%sBack to normal!\n", N);
}
