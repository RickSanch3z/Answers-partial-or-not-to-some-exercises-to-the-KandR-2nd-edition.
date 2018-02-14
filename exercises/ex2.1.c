#include <stdio.h>
#include <limits.h>
#include <float.h>

// This is a partial solution. Read the description below.

/*  program to determine the ranges of types "char", "short",
	  "int", and "long", both "signed" and "unsigned" from
	  standard "<limints.h>" and types "float", "double", 
    and "long double" from "<float.h>" headers.

    And compute ranges of the floating-point types.
    Integers is more or less trivial to compute (compute 
    version not included here).

    From K&R (non exact citation):
    Sizes of the floating-point objects are implementation-defined. 
    So the sizes of "float", "double", and "long double" could 
    represent one, two or three distinct sizes.

    If the previous statement hold true nowadays, calculated values 
    floating-point types would fail (at least for some types) on 
    some platforms.
*/
/*	Useful site to visualize IEEE-754 single precision
    floating-point number:
    https://www.h-schmidt.net/FloatConverter/IEEE754.html
*/

int main()
{
	printf("Predefined values (from '<limits.h>' and '<float.h>') of 'float', 'double', and 'long double'\n\n\n");
	printf("Maximum numeric value of type 'char':\n %d\n", CHAR_MAX);
	printf("Minimum numeric value of type 'char':\n %d\n\n", CHAR_MIN);
	
	printf("Maximum numeric value of type 'signed char':\n %d\n", SCHAR_MAX);
	printf("Minimum numeric value of type 'signed char':\n %d\n\n", SCHAR_MIN);
	
	printf("Maximum numeric value of type 'unsigned char':\n %d\n\n", UCHAR_MAX);
	
	printf("Maximum numeric value of type 'short int' or 'short':\n %d\n", SHRT_MAX);
	printf("Minimum numeric value of type 'short int' or 'short':\n %d\n\n", SHRT_MIN);
	
	printf("Maximum numeric value of type 'unsigned short int' or 'unsigned shor':\n %d\n\n", USHRT_MAX);
	
	printf("Maximum numeric value of type 'int':\n %d\n", INT_MAX);
	printf("Minimum numeric value of type 'int':\n %d\n\n", INT_MIN);
	
	printf("Maximum numeric value of type 'unsigned int':\n %u\n\n", UINT_MAX);
	
	printf("Maximum numeric value of type 'long int' or 'long':\n %ld\n", LONG_MAX);
	printf("Minimum numeric value of type 'long int' or 'long':\n %ld\n\n", LONG_MIN);
	
	printf("Maximum numeric value of type 'unsigned long int' or 'unsigned long':\n %lu\n\n", ULONG_MAX);
	
	printf("Maximum numeric value of type 'float':\n %f\n", FLT_MAX);
	printf("Minimum numeric value of type 'float':\n %f\n\n", (-1) * FLT_MAX);
	
	printf("Maximum numeric value of type 'double':\n %f\n", DBL_MAX);
	printf("Minimum numeric value of type 'double':\n %f\n\n", (-1) * DBL_MAX);
	
	printf("Maximum numeric value of type 'long double':\n %Lf\n", LDBL_MAX);
	printf("Minimum numeric value of type 'long double':\n %Lf\n\n", (-1) * LDBL_MAX);
	
	
	
	printf("\n\n\nCalculated values of 'float', 'double', and 'long double'\n\n\n");
	int j;
	float f = 1.0;	//1bit length sign field
			//8bit length exponent field (127 max)
			//1bit implicit(not present in the field) + 23bit length in mantissa
			//field
	double d = 1.0;
	long double ld = 1.0;
	
	// First fill the mantissa part.
	// Multiplying by 2
	// will shit to the left the integer part and will
	// inrecemnt the exponent part.
	// Adding 1 will fill the mantissa part.
	// "j == 23" is equal to number of bits in mantissa field.
	for (j = 1; j <= 23; ++j) {
		f = f * 2.0;
		f = f + 1.0;
	}
	// Then just multiply by 2. This will shift the
	// the integer part to the left and increment the exponent by 1.
	// And thus changing
	// the position of the floting-point to follow the
	// left most significant bit (point will be placed
	// in front of the bit. This bit is implicit one. He
	// is not present in mantissa bits field). Refer to
	// IEEE 754.
	// "j == 104" is equal to difference between exponent max and
	// 23bit length in mantissa
	for (j = 1; j <= 104; ++j) {
		f = f * 2.0;
	}
	
	printf("Float MAX:\n %f.\nFloat MIN:\n %f.\n", f, (-1.0) * f);
	
	
	// idem for type "double". But with different lengt of
	// mantissa field and exponent max.
	for (j = 1; j <= 52; ++j) {
		d = d * 2.0;
		d = d + 1.0;
	}
	for (j = 1; j <= 971; ++j) {
		d = d * 2.0;
	}
	printf("Double MAX:\n %f.\nDouble MIN:\n %f.\n", d, (-1.0) * d);
	
	
	/* According to the GNU GSL (GNU Scientific Library) 
	"long double" is platform dependant. The IEEE standard 
	only specifies the minimum precision of extended precision 
	numbers, while the precision of "double" is the same on 
	all platforms.
	
	From: https://www.developerfusion.com/article/4691/floatingpoint-in-net-part-i-concepts-and-format/4/
	The IEC 60559 standard doesn't specify exact values for the 
	parameters of the extended floating-point format. It only 
	specifies minimum values.
	Since 8087 Intel processors use 80bits extended format. 
	With 15bits for the exponent and 64bits for the significand. 
	The leading bit (MSB) of the significand is explicitly 
	present.
	*/
	for (j = 1; j <= 63; ++j) {
		ld = ld * 2.0;
		ld = ld + 1.0;
	}
	for (j = 1; j <= 16320; ++j) {
		ld = ld * 2.0;
	}
	printf("Long double MAX:\n %Lf\n", ld);
	printf("Long double MIN:\n %Lf\n\n", (-1.0) * ld);


	return 0;
}
