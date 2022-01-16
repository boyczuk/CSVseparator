#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

FILE *file;
size_t nread;

float a1_average, a2_average, a3_average, a4_average;
char *a1, *a2, *a3, *a4;
int culm_a1, culm_a2, culm_a3, culm_a4, inquote;


typedef struct student student;
struct student {
    char *surname;
    char *firstname;
    char *assignment_1;
    char *assignment_2;
    char *assignment_3;
    char *assignment_4;

};

student parse_student(char *e){
    student s;
    size_t max_width = 64; //possibly change to 90
    
    s.surname = malloc(max_width);
    s.firstname = malloc(max_width);
    s.assignment_1 = malloc(max_width);
    s.assignment_2 = malloc(max_width);
    s.assignment_3 = malloc(max_width);
    s.assignment_4 = malloc(max_width);

    /* setting the delimiter to commas, and putting each into their respective attribute of the student struct */
    printf("e: %s\n", e);
    int n = sscanf(e, "%[^','],%[^','],%[^','],%[^','],%[^','],%[^',']",
                s.surname,
                s.firstname,
                s.assignment_1,
                s.assignment_2,
                s.assignment_3,
                s.assignment_4); 
    return (s);
}

char *remove_whitespace(char *str){
    int i = 0;
    int j = 0;
    while (str[i]){
        if (str[i] != ' '){
            str[j++] = str[i];
        }
        i++;
    }
    str[j] = '\0';
    return (str);
}


void print_students(student s){
    /* whitespace removal necessary to properly convert fields to integer for average calculation */
    a1 = remove_whitespace(s.assignment_1);
    a2 = remove_whitespace(s.assignment_2);
    a3 = remove_whitespace(s.assignment_3);
    a4 = remove_whitespace(s.assignment_4);

    
    if (isdigit(*a1)){
        /* printf("a1: %s\n",a1); */
        a1_average += atoi(a1);
        culm_a1++;
    }
    if (isdigit(*a2)){
        /* printf("a2: %s\n",a2); */
        a2_average += atoi(a2);
        culm_a2++;
    }
    if (isdigit(*a3)){
        /* printf("a3: %s\n",a3); */
        a3_average += atoi(a3);
        culm_a3++;
    }
    if (isdigit(*a4)){
        /* printf("a4: %s\n",a4); */
        a4_average += atoi(a4);
        culm_a4++;
    }
    /* each field below is hard coded and separated by the commas found in the csv file
    remove comments to show all lines separated into their fields */

    /* printf("surname: %s\n", s.surname);
    printf("firstname: %s\n", s.firstname);
    printf("a1: %s\n", s.assignment_1);
    printf("a2: %s\n", s.assignment_2);
    printf("a3: %s\n", s.assignment_3);
    printf("a4: %s\n", s.assignment_4); */
}


int main(void) {
    //int line_count = lines();
    //printf("The line count is: %d\n",line_count);

    //Change "grades2.txt" to relevant text file
    file = fopen("grades3.txt","r");
    if(!file){
        fprintf(stderr, "cant open the file");
        exit(1);
    }
    char buf[100];
    while (fgets(buf,100,file)){
        student s = parse_student(buf);
        print_students(s);
    }
    fclose(file);

    /* if amount of assignments is lower than 4 NaN will apear could use if statement to simplify further
    but the nan statement helps debugging
    
    This could also be done using a for loop with the same logic, just simplier for debugging to hard code */
    printf("A1 %2.1f\n",a1_average/culm_a1);
    printf("A2 %2.1f\n",a2_average/culm_a2);
    printf("A3 %2.1f\n",a3_average/culm_a3);
    printf("A4 %2.1f\n",a4_average/culm_a4);


}
    
