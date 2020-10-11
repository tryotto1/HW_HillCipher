//#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

// cipher text size
int m = 257;
int d = 5;

// cipher text arr with int and string
int cipher_int[2000];
int cipher_arr[300][10];
char cipher_str[2000] = "HRDKHUBHAAMAEQMTMZSHGBAKFUBHAASYRXUNKYUAATQCTLUTOGEWVAJGVEIIYTKIOTQRXXQVSQLISVVOCNGCUXPKPIUBOHTVKCFKWNJSEZYSSUTUOESIXKAPVFXNZHAOQTLCGYJVAEHLNNKEESQMKSHKKDFCNZSRHRDKHSDKFXVPTGMKRUPZBIKEVNYEKXMFXKFYMWYUDZDENEWNKDAOUXGPCXZDLCSNFGCMCSNUAOJDBLQTAHEWYZCHQJYKSNUWOKQKONZGOKDXGUXKEMWQMCFGUEAVKHDIIATCHVTGYMGKJMLNPCNAYKMIRWEETIYQKELEGLQOVKISFNUDAJQIQYBXQTMZSHGBAKFZRCNWRSODAFKKXWGAZGDBIUDDHCUDFRFOVSZXADSHYSGLTQBMNEMKDCFSOZSRDYLIHIAXCMGMFEIDNZKOVJEOIEFNWWQEDRLZYZIZXADSHYSGLJYFWDUAKSIOGOZOXWYPBUFEPNBIRJUJNDZJJYMURKNCIKPWLRMRIAGVSXTYNIWPROHLDHQOMBEKZURQCLQOVKISFNUAFQBHGPCLHZTPJVPXIZKLQSNVKIJAEITTNVSVWNFYVATDEMKDCTGIHKZTVGZYXTYQEDBACFMNCAHRDKHSDKFXZXXGMJOSLPSZBMOILMMWRALAFFMNXXDYFBIYQVVOHSWKGBIRJGTBYQLKIJAEQBTAXGFGAVUIJADHQKLFWRJXYFVIGGQZNBHSUIYOZALSKIABLWQNXNXKOAJAIKHXODXWORVDOGBMHOPLQJZALQJZALIKTKLENZHQAVYUEUFEVLUXHGOWNMGWXUIAHGQOMNCKFQLIPBNKVWDLNGMJCOBFKIGBYWPAHMMPQLUTOGECXITZVVAJEOIDCNWMFNLOBGQXCYFWQFWVXWRKWYGBFHJVLBAWBOUQEKHZHSZZIZARYITDCLQFPGBTJMQVSQLIHPEJONCYMZWTVJVZOBOMOHPSXMPUKVAGXIPOQUQUQBCKXZJSZAHEWYHAEMKOJCCCFBEUKVNCAWANSNXISVVOWHQGQFBGWKQEGBIFRGIZUJQWIMFANTGBHWGVAGXIPOQUQTTRMWDHDGRFENKYPZVCLNQAUBTZSRYGVGOWSVROENABMZTOHZRQFUEVPLLIODEYRYLUTOGPYAFHJFIVOSFMPBSHLEKWYWJYTFYETAZQCRFTFHOMACOQVTWKLKYMGIMQDSYNWMFNIEITWMBVVWANBQFVUSKZOTLCCWABAGHWZBZHRDKHDTUOMUUUGQICHNUUQFJYUCQUO";

// plain text of row m
int p[300] = { 0 };
int plain_arr[300][10] = { 0 };

// d_it, inverse K, array I
int d_it[300][10];
int k_1[5][5];
float I_arr[5] = { -999, -999, -999, -999, -999 };

// monogram frequency
float f[26] = { 0.082, 0.015, 0.028, 0.043, 0.127, 0.022, 0.020, 0.061, 0.070, 0.002, 0.008, 0.004, 0.024, 0.067, 0.015, 0.019, 0.001, 0.060, 0.063, 0.091, 0.028, 0.010, 0.024, 0.002, 0.020, 0.001 };

int main() {
    // change string to int value
    for (int i = 0; i < 1285; i++)
        cipher_int[i] = (int)(cipher_str[i] - 65);

    // divide cipher text into m blocks
    for (int i = 0; i < m; i++)
        for (int j = 0; j < d; j++)
            cipher_arr[i][j] = cipher_int[i * 5 + j];

    // initialize d_it array    
    for (int i = 0; i < m; i++) {
        int tmp_sum = 0;

        for (int j = 0; j < d; j++) {
            tmp_sum += cipher_arr[i][j];

            d_it[i][j] = tmp_sum % 26;
        }
    }

    // initialize K inverse with value 1
    for (int i = 0; i < d; i++)
        for (int j = 0; j < d; j++)
            k_1[i][j] = 1;

    // initialize iml value
    float iml = -log2f(f[0]);

    // main algorithm - lexicographical order of vector x
    for (int d_4 = 0; d_4 < 26; d_4++) {
        printf("d_4 val : %d \n", d_4);
        for (int d_3 = 0; d_3 < 26; d_3++)
            for (int d_2 = 0; d_2 < 26; d_2++)
                for (int d_1 = 0; d_1 < 26; d_1++)
                    for (int d_0 = 0; d_0 < 26; d_0++) {
                        int tmp_darr[5] = { d_0, d_1, d_2, d_3, d_4 };

                        // count how many zeros are continuous
                        int t = 0;
                        while (t < 5) {
                            if (tmp_darr[t] == 0)
                                t++;
                            else
                                break;
                        }
                        if (t == 5)
                            continue;

                        // update iml and p value
                        for (int i = 0; i < m; i++) {
                            iml -= log2f(f[p[i]]) / m;
                            p[i] = (p[i] + d_it[i][t]) % 26;
                            iml += log2f(f[p[i]]) / m;
                        }

                        // x should not be all-zero modulo 2 or 13
                        if ((d_0 % 2 != 0 && d_0 % 13 != 0) || (d_1 % 2 != 0 && d_1 % 13 != 0) || (d_2 % 2 != 0 && d_2 % 13 != 0) || (d_3 % 2 != 0 && d_3 % 13 != 0) || (d_4 % 2 != 0 && d_4 % 13 != 0))
                            /*if ((d_0 % 26 != 0) || (d_1 % 26 != 0) || (d_2 % 26 != 0 ) || (d_3 % 2 != 0 && d_3 % 13 != 0) || (d_4 % 2 != 0 && d_4 % 13 != 0))*/
                        {
                            int min_idx = 0;

                            // find a column from inverse K which has the smallest IML
                            for (int i = 1; i < d; i++)
                                if (I_arr[i] < I_arr[min_idx])
                                    min_idx = i;

                            // if the IML value is smaller than iml
                            if (I_arr[min_idx] < iml) {
                                // replace corresponding IML value in I with iml
                                I_arr[min_idx] = iml;

                                // replace the column y with current column x
                                for (int j = 0; j < 5; j++)
                                    k_1[j][min_idx] = tmp_darr[j];
                            }
                        }
                    }
    }

    // print out inverse K array
    printf("--------- inverse K array ---------\n");
    for (int i = 0; i < d; i++) {
        for (int j = 0; j < d; j++)
            printf("%d ", k_1[i][j]);
        printf("\n");
    }
    printf("-----------------------------------\n");

    // decipher all the text
    for (int i = 0; i < m; i++) {
        for (int k = 0; k < d; k++) {
            int tmp_sum_plain = 0;

            for (int j = 0; j < d; j++)
                tmp_sum_plain += (cipher_arr[i][j] * k_1[j][k]);

            plain_arr[i][k] = tmp_sum_plain % 26;
        }
    }

    // print out all the plain text
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < d; j++)
            printf("%c ", (plain_arr[i][j] + 65));

        printf("\n");
    }

    // for delay in exe file
    system("pause > nul");
    return 0;
}