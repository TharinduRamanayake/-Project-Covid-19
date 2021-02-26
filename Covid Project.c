#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*TharinduRamanayake*/

/**
 * return the position of the key within the csv header
 * return -1 if the key is not found
 * @csv_header header of the csv file
 * @key the name of the field you are looking for
 */
int getFieldIndex(char *csv_head, char *key);

/**
 * return the value of the ith field of the line
 * works only with integer fields
 * @line the line from which to extract the value
 * @index of the field
 * Can't fail unless the CSV file is miss formed or index is erroneous
 */
int getFieldValue(char *line, int field);

/**
 * return the value of the ith field of the line
 * works only with strings
 * @line the line from which to extract the value
 * @index of the field
 * @results where results are to be placed
 * return 1 if the field is found 0 otherwise
 * Can't fail unless the CSV file is miss formed
 */
void getFieldString(char *line, int filed, char *results);


/**
 * The main function
 * User is expected to give two fileds country and field (that is cases or
 * deaths). We will assume the given country is always there
 */

#define COUNTRY "countriesAndTerritories"
// in the CSV header this is what the country is called

#define DATE "dateRep"

#define DATAFILE "covid-19.csv"
// where the data is kept

int main(int argc, char **argv)
{
  if(argc != 3) { // wrong number of arguments Maximum Arguments are 3
    printf("You need to give two arguments\n");
    return -1;
  }

  char *country = argv[1];
  char *field   = argv[2]; //argv[0]= .exe file name

  printf("Analysing %s's data for the maximum %s\n",
	 country, field);

  char line[300];

  // lets open the file
  FILE *fp = fopen(DATAFILE,"r");
  if(fp == NULL) {//did n't have covid file or miss it show this message DATAFILE= covid-19 file
    printf("Can't open %s\nDid you download it???",DATAFILE);
    return -1;
  }

  if(fgets(line, 300, fp) == NULL)
    { //read about fgets
    // fgets reads 300 chars or until it finds a newline or EOF
    printf("Can't read the data file\n"); //If the LINE NULL show this error
    return -1;
    }

  int countryIndex = getFieldIndex(line, COUNTRY);//like as 3rd
  int fieldIndex   = getFieldIndex(line, field);// like as 3rd
  int dateIndex    = getFieldIndex(line, DATE); //getFieldIndex(line,DATE) this return value=int dateIndex


  if(countryIndex == -1 ||
     fieldIndex   == -1 ||
     dateIndex    == -1) //one of these are true if show the printf message
    {
    printf("Can't find the fields in header\n");
    return -1;
    }

  // lets read one line at a time.
  // see if the line corresponds to the country
  // if so extract the filed (used wants)
  //TharinduRamanayake
  int previous = 0, current = 0, max = 0;
  char maxDate[11];
  char countryName[40];

  while(fgets(line, 300, fp) != NULL) {

    getFieldString(line, countryIndex, countryName); //extract country name

      // if extracted name is what used asked
    if(strcmp(countryName, country) == 0) {
		current = getFieldValue(line, fieldIndex);
		if(current>=max) {
            previous=current;
			max = previous;
			getFieldString(line,dateIndex,maxDate); //this is for get maximum country deaths & date
		}

		previous = current;
    }
  }
	  printf("In %s max %s was %d and was reported on %s\n",country, field, max, maxDate);
  return 0;
}
/*TharinduRamanayake*/

int getFieldIndex(char *head, char *key)
{
  //implement this
	char word[30];
	for(int i=0 , j =0 , index = 1 ; i <= strlen(head) ; i++){
		if(head[i] == ',' ){//check one by one character and "," for break point
			word[j]='\0';
			if(strcmp(word, key) == 0){
				return index;
			}
			j=0;
			index += 1;
            }
		else
            {
			word[j]=head[i];
			j +=1;
			}

	}

  return -1;
}
/*TharinduRamanayake*/
int getFieldValue(char *line, int filed)//getFieldValue(line, fieldIndex)
{
  // implement this
  	char word[20];
	int value,i,j,index;

	for(i = 0,  j=0 , index=1; i <= strlen(line) ; i++){
		if(line[i]==',' ){
			word[j]='\0';
			if(index == filed){
				value = atoi(word);
				return value;
			}
			j=0;
			index ++;
			}
			else
                {
				word[j]=line[i];
				j++;
                }
		}

	return -1;
}

void getFieldString(char *line, int filed, char *res)/*getFieldString(line, countryIndex, countryName)
                                                            &(line, dateIndex, maxDate)*/

{
  // implement this
	char word[40];

	for(int i = 0,  j=0 , index=1; i <= strlen(line) ; i++){
		if(line[i]==',' ){
			word[j]='\0';
			if(filed == index){
				strcpy(res,word);
				return;
			}
			j=0;
			index++;
			}
			else
                {
				word[j]=line[i];
				j++;
                }
		}
  return;
}
