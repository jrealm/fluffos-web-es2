// profile.c

int main(object me, string arg)
{
        seteuid(geteuid(this_player(1)));

	PROFILE_D->make_profile(arg);
	write("Result written to /PROFILE\n");

	return 1;
}
int help (object me)
{
        write(@HELP
���O�榡: profile
 
turns on command profiling, the result will be saved to /PROFILE
 
HELP
);
        return 1;
}
 
