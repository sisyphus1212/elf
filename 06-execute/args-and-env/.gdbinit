
shell echo -e "\nset args arg1 arg2\n"
set args arg1 arg2

shell echo -e "\nset breakpoints\n"
b main

shell echo -e "\nstart running\n"
r

shell echo -e "\nprint stack register value\n"
p $esp

shell echo -e "\nprint value in (\$esp), argc\n"
x $esp

shell echo -e "\nprint value in (\$esp+4), argv pointer\n"
x $esp+4

shell echo -e "\nprint value in (\$esp+8), envp pointer\n"
x $esp+8
