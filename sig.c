int main()
{
	/*setpgid(0, 0);*/
	kill(getpid(), 14);
	printf("!!!\n");
	return 0;
}
