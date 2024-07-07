#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ARR 5000

/*  Function: take_photo()
    Description: Simulates taking a photo as a black-and-white image represented by
                 an array of characters '1' and '0'. The photo is stored in the out[] array.

    Output: out[]   - an array of characters to store the photo data, as a string of 1 and 0 characters
    Output: rows    - an address to an integer to store the number of rows in the photo
    Output: cols    - an address to an integer to store the number of columns in the photo

    Returns: the total number of characters in the photo data OR 0 if no photo was taken
    
*/
int take_photo(unsigned char out[], int* rows, int* cols);

unsigned char get_bit(unsigned char byte, int bit);
unsigned char set_bit(unsigned char byte, int bit);
unsigned char clear_bit(unsigned char byte, int bit);
void print_raw(unsigned char raw_string[], int rows, int cols);
int pack_bits(unsigned char unpacked_string[], int num_chars, unsigned char packed_result[]);
void print_packed(unsigned char packed[], int rows, int cols);
int encode_bits(unsigned char packed[], int packed_size, unsigned char encoded_result[]);
void print_encoded(unsigned char encoded[], int encoded_size, int rows, int cols);

int main() {
    unsigned char img_array[MAX_ARR], packed_bits[MAX_ARR], encoded_result[MAX_ARR];
    int cols, rows, size, packed_size, encoded_size;

    while(1){
        size=take_photo(img_array, &rows, &cols);
        if (size==0){
            break;
        }

        print_raw(img_array, rows, cols);
        packed_size=pack_bits(img_array, size, packed_bits);
        print_packed(packed_bits, rows, cols);
        encoded_size=encode_bits(packed_bits, packed_size, encoded_result);
        print_encoded(encoded_result, encoded_size, rows, cols);
        printf("Sizes: raw = %d bytes, packed = %d bytes, encoded = %d bytes", rows*cols, packed_size, encoded_size);
    }
    return 0;
}

void print_raw(unsigned char raw_string[], int rows, int cols) {
    printf("\nRaw Photo: %d bytes\n", rows*cols);

    for (int y=0; y<rows; y++){ //controls when to print the next line
        for (int x=y*cols; x<y*cols+cols; x++){ //keeps track of the correct index
            if (raw_string[x]=='1'){
                printf("*");
            } else {
                printf(".");
            }
        }
        printf("\n"); //next line
    }
}

int pack_bits(unsigned char unpacked_string[], int num_chars, unsigned char packed_result[]) {
    int size = 0;

    for (int i = 0; i < num_chars; i += 8) { //reads every 8 bytes
        unsigned char packed_char = 0; //reset byte

        for (int bit = 0; bit < 8; bit++) { //loops through bits to pack into char

            if (unpacked_string[i + bit] == '1') { //if 1 set bit if 0 skip
                packed_char = set_bit(packed_char, bit);
            }
        }
        packed_result[size++] = packed_char; //sets new packed byte
    }
    return size;
}

void print_packed(unsigned char packed[], int rows, int cols) {
    int index=0;
    printf("\nPacked Photo: %d bytes\n", (rows*cols)/8);

    for (int i=0; i<(rows*cols)/8; i++){ //keeps index of bytes
        for (int bit = 0; bit < 8; bit++) { //prints bits
            if (get_bit(packed[i], bit)==1){
                printf("*");
            } else {
                printf(".");
            }
            index++;
            
            if (index==cols){ //tracks when to print next line
                printf("\n");
                index=0;
            }
        }
    }
}


int encode_bits(unsigned char packed[], int packed_size, unsigned char encoded_result[]){
    int counter=0, index=0;
    unsigned char previous_bit=1;

    for (int i=0; i<packed_size; i++){

        for (int bit = 0; bit < 8; bit++) {

            if (get_bit(packed[i], bit)==previous_bit){ //if matches last bit keep counting
                counter++;
            } else { //if bit changed set new byte and count next bit
                encoded_result[index++]=counter;
                counter=1; //counter set to 1 to include current index
            }
            previous_bit=get_bit(packed[i], bit); //set new pevious bit
        }
    }

    encoded_result[index++] = counter; //add last byte
    return index; //return size
}

void print_encoded(unsigned char encoded[], int encoded_size, int rows, int cols){
    int counter=0;
    printf("\nEncoded Photo: %d bytes\n", encoded_size);

    for (int i=0; i<encoded_size; i++){ //loop encoded
        for (int j=0; j<encoded[i]; j++){ //print encoded
            if (i%2==0){ //when to print * or . based off index
                printf("*");
            } else {
                printf(".");
            }
            counter++; //keep track of next line

            if (counter==cols){//print to next line
                counter=0;
                printf("\n");
            }
        }
    }
}

unsigned char get_bit(unsigned char byte, int bit) {
    return (byte >> bit) & 1;
}

unsigned char set_bit(unsigned char byte, int bit) {
    return byte | (1 << bit);
}

unsigned char clear_bit(unsigned char byte, int bit) {
    return byte & ~(1 << bit);
}