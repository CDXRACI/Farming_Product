1.Low level langue: Assembly / machine langue
		  0000 1001 0100 1101...   =>1. efficient
					     2. machine architect
					     3. less memory
					     4. fast
 

2. middle langue: C "The mother of languages"
				(C)
				 |
		             ----------
			    |	|      |
			    C++ Python C#
		"Nearly every language uses or is influenced by C"
		

3. high level . 2. difficult to work with low level hardware
		3. More memory
		4. slow




*note: 1. C is not object oriented
       2. C++ is an extension of C

*WHAT NEED:
	1. IDE ( Text editor )
	2. compiler ( GCC )

* Program

	1. Khai bao va khoi tao gia tri 
		1.1 Khai bao thu vien
		1.2 Khai bao hang
		1.3 Khai bao bien
		1.4 Khai bao ham su dung
	2. Than ham ( do something )
		2.1 Loop main
			- Tinh toan cong tru nhan chia 
			- lay du lieu tu input xu ly de ket qua ra cho output
			- thuc hien cac function da duoc khai bao ben trong thong qua 1 loi goi ham
	3. Ket
		3.1 chua cac ham con voi muc dich xu ly khi duoc goi trong ham main hoac qua 1 bo dinh thoi
		1 ngat ...

* comment
	// in a line
	/* */ in a paragraph

* print and scan with escape sequences 

	print: in ra noi dung co trong dau nhay don ""
	printf("format_type", argument_list );
	format_type: data type will be printed out.
	argument_list: la noi nhap doi so co kieu la bien ( mang ) se duoc in ra phu thuoc vao format_type
	
	%d  for printing integers 	                %s for printing strings
	%f  for printing floating-point numbers 	%p for printing memory addresses
	%c  for printing characters	                %x for printing hexadecimal values

	printf("hello world")
	print is return function -> return: the number of characters printed
				 ->       : fail if an error occours,a negative value is returned.

	width:
	It is the sub-specifier that denotes the minimum number of characters that will be printed.
	printf("%25s", some_string);
	or
	printf("%*s", 25, some_string);
	output: 
	<----space--->+hello world=25 characters
	 Precision
	Precision subspecifier meaning differs for different format specifiers it is being used with.

	For Integral data(d, i, u, o, x, X): Specifies the minimum number of digits to be printed. But unlike the width sub-specifier, instead of white spaces, this sub-specifier adds leading zeroes to the number. If the number has more digits than the precision, the number is printed as it is.
	For Float or Double Data(f, e, a, A): Specifies the number of digits to be printed after the decimal point.
	For String (s): Specifies the length of the string to be printed.
	Example

printf("%.10d", some_integer);
printf("%.3f", some_float);
printf("%.25s", some_string);



	scanf: quet noi dung duoc nhap tu man hinh roi dua vao 1 mang ky tu 
	scanf("%d", &d1)
		|    |
read an integer<-    -> scanf puts that read value "A the address of "d1" vairable

escape sequences:

    int num = 2451;
    float dec = 12.45126;
    char* str = "GeeksforGeeks";


    printf("For integers: %.10d\n", num);
    printf("For floats: %.2f\n", dec);
    printf("For strings: %.5s", str);
    long var = 3000000000;
    printf("Using %%d: %d", var);
    printf("\nUsing %%ld: %ld", var)
Output
Using %d: -1294967296
Using %ld: 3000000000
