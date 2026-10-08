#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TRANSACTIONS 1000
#define DATE_LEN 15
#define TYPE_LEN 10

/* ============================================================
   TRANSACTION STRUCTURE
   ============================================================ */

typedef struct
{
    int transactionID;
    int customerID;
    char date[DATE_LEN];
    char type[TYPE_LEN];
    double amount;

} Transaction;


/* ============================================================
   INTERNAL ALGORITHM STATISTICS
   These are NOT displayed to the user.
   They exist only for internal algorithm selection/evaluation.
   ============================================================ */

long long mergeComparisons = 0;
long long quickComparisons = 0;


/* ============================================================
   FUNCTION PROTOTYPES
   ============================================================ */

void clearInputBuffer(void);

void addTransaction(Transaction transactions[], int *n);

void displayTransactions(Transaction transactions[], int n);
void displaySingleTransaction(Transaction t);

int transactionIDExists(Transaction transactions[], int n, int id);


/* ---------- Automatic Sorting ---------- */

void automaticSort(Transaction transactions[], int n);
int isNearlySorted(Transaction transactions[], int n);

void mergeSort(Transaction transactions[], int left, int right);
void merge(Transaction transactions[], int left, int mid, int right);

void quickSort(Transaction transactions[], int low, int high);
int partition(Transaction transactions[], int low, int high);


/* ---------- Searching ---------- */

void sortByTransactionID(Transaction transactions[], int left, int right);
int binarySearch(Transaction transactions[], int n, int key);

void searchTransaction(Transaction transactions[], int n);


/* ---------- Reports ---------- */

void generateReport(Transaction transactions[], int n);

void highestLowest(Transaction transactions[], int n);

void customerTransactions(Transaction transactions[], int n);

void transactionSummary(Transaction transactions[], int n);


/* ---------- Utility ---------- */

void copyTransactions(Transaction source[],
                      Transaction destination[],
                      int n);


/* ============================================================
   MAIN
   ============================================================ */

int main()
{
    Transaction transactions[MAX_TRANSACTIONS];

    int n = 0;
    int choice;

    printf("\n");
    printf("============================================================\n");
    printf("              BANKING TRANSACTION SYSTEM\n");
    printf("============================================================\n");

    do
    {
        printf("\n");
        printf("------------------------------------------------------------\n");
        printf("                         MAIN MENU\n");
        printf("------------------------------------------------------------\n");

        printf("  1. Add Transaction\n");
        printf("  2. View All Transactions\n");
        printf("  3. Search Transaction\n");
        printf("  4. Transaction Report\n");
        printf("  5. Customer Transactions\n");
        printf("  6. Transaction Summary\n");
        printf("  7. Highest / Lowest Transaction\n");
        printf("  0. Exit\n");

        printf("------------------------------------------------------------\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);
        clearInputBuffer();

        switch(choice)
        {
            case 1:
                addTransaction(transactions, &n);
                break;

            case 2:
                displayTransactions(transactions, n);
                break;

            case 3:
                searchTransaction(transactions, n);
                break;

            case 4:
                generateReport(transactions, n);
                break;

            case 5:
                customerTransactions(transactions, n);
                break;

            case 6:
                transactionSummary(transactions, n);
                break;

            case 7:
                highestLowest(transactions, n);
                break;

            case 0:
                printf("\nThank you for using Banking Transaction System.\n");
                printf("Have a great day!\n");
                break;

            default:
                printf("\nInvalid choice. Please try again.\n");
        }

    } while(choice != 0);

    return 0;
}


/* ============================================================
   CLEAR INPUT BUFFER
   ============================================================ */

void clearInputBuffer(void)
{
    int c;

    while((c = getchar()) != '\n' && c != EOF)
    {
        /* discard */
    }
}


/* ============================================================
   CHECK DUPLICATE TRANSACTION ID
   ============================================================ */

int transactionIDExists(Transaction transactions[],
                        int n,
                        int id)
{
    int i;

    for(i = 0; i < n; i++)
    {
        if(transactions[i].transactionID == id)
        {
            return 1;
        }
    }

    return 0;
}


/* ============================================================
   ADD TRANSACTION
   ============================================================ */

void addTransaction(Transaction transactions[], int *n)
{
    Transaction t;

    if(*n >= MAX_TRANSACTIONS)
    {
        printf("\nTransaction storage is full.\n");
        return;
    }

    printf("\n============================================================\n");
    printf("                    ADD TRANSACTION\n");
    printf("============================================================\n");


    /* Transaction ID */

    while(1)
    {
        printf("Transaction ID : ");
        scanf("%d", &t.transactionID);
        clearInputBuffer();

        if(transactionIDExists(transactions,
                                *n,
                                t.transactionID))
        {
            printf("Transaction ID already exists.\n");
            printf("Please enter another ID.\n");
        }
        else
        {
            break;
        }
    }


    /* Customer ID */

    printf("Customer ID    : ");
    scanf("%d", &t.customerID);
    clearInputBuffer();


    /* Date */

    printf("Date (DD/MM/YYYY): ");
    scanf("%14s", t.date);
    clearInputBuffer();


    /* Transaction Type */

    while(1)
    {
        printf("Type (Credit/Debit): ");
        scanf("%9s", t.type);
        clearInputBuffer();

        if(strcmp(t.type, "Credit") == 0 ||
           strcmp(t.type, "credit") == 0 ||
           strcmp(t.type, "CREDIT") == 0)
        {
            strcpy(t.type, "Credit");
            break;
        }

        if(strcmp(t.type, "Debit") == 0 ||
           strcmp(t.type, "debit") == 0 ||
           strcmp(t.type, "DEBIT") == 0)
        {
            strcpy(t.type, "Debit");
            break;
        }

        printf("Please enter either Credit or Debit.\n");
    }


    /* Amount */

    while(1)
    {
        printf("Amount         : ");
        scanf("%lf", &t.amount);
        clearInputBuffer();

        if(t.amount <= 0)
        {
            printf("Amount must be greater than zero.\n");
        }
        else
        {
            break;
        }
    }


    transactions[*n] = t;

    (*n)++;

    printf("\nTransaction added successfully.\n");
}


/* ============================================================
   DISPLAY TABLE HEADER
   ============================================================ */

void displaySingleTransaction(Transaction t)
{
    printf("%-15d %-15d %-15s %-12s Rs. %-12.2lf\n",
           t.transactionID,
           t.customerID,
           t.date,
           t.type,
           t.amount);
}


/* ============================================================
   DISPLAY ALL TRANSACTIONS
   ============================================================ */

void displayTransactions(Transaction transactions[], int n)
{
    int i;

    if(n == 0)
    {
        printf("\nNo transactions available.\n");
        return;
    }

    printf("\n");
    printf("==========================================================================\n");
    printf("                         TRANSACTION RECORDS\n");
    printf("==========================================================================\n");

    printf("%-15s %-15s %-15s %-12s %-17s\n",
           "Transaction ID",
           "Customer ID",
           "Date",
           "Type",
           "Amount");

    printf("--------------------------------------------------------------------------\n");

    for(i = 0; i < n; i++)
    {
        displaySingleTransaction(transactions[i]);
    }

    printf("--------------------------------------------------------------------------\n");

    printf("Total Transactions: %d\n", n);
}


/* ============================================================
   CHECK WHETHER DATA IS NEARLY SORTED
   Used internally for choosing the sorting algorithm.
   ============================================================ */

int isNearlySorted(Transaction transactions[], int n)
{
    int i;
    int disorder = 0;

    if(n <= 1)
    {
        return 1;
    }

    for(i = 1; i < n; i++)
    {
        if(transactions[i].amount < transactions[i - 1].amount)
        {
            disorder++;
        }
    }

    /*
       If less than approximately 20% of adjacent
       elements are out of order, consider it nearly sorted.
    */

    if(disorder <= n / 5)
    {
        return 1;
    }

    return 0;
}


/* ============================================================
   AUTOMATIC SORT SELECTION
   ============================================================ */

void automaticSort(Transaction transactions[], int n)
{
    /*
       The user does NOT select the algorithm.

       Internal strategy:

       Small dataset:
           Quick Sort

       Large dataset:
           Merge Sort

       Nearly sorted dataset:
           Merge Sort

       This keeps the interface simple while the
       AOA algorithms operate internally.
    */

    if(n <= 1)
    {
        return;
    }


    /* Reset internal counters */

    mergeComparisons = 0;
    quickComparisons = 0;


    /*
       Small datasets:
       Quick Sort is efficient and simple.
    */

    if(n < 20)
    {
        quickSort(transactions, 0, n - 1);
    }


    /*
       Large or nearly sorted datasets:
       Merge Sort provides predictable performance.
    */

    else if(n >= 20 || isNearlySorted(transactions, n))
    {
        mergeSort(transactions, 0, n - 1);
    }
}


/* ============================================================
   MERGE SORT
   ============================================================ */

void merge(Transaction transactions[],
           int left,
           int mid,
           int right)
{
    int i;
    int j;
    int k;

    int n1 = mid - left + 1;
    int n2 = right - mid;

    Transaction *L;
    Transaction *R;


    L = (Transaction *)malloc(n1 * sizeof(Transaction));
    R = (Transaction *)malloc(n2 * sizeof(Transaction));


    if(L == NULL || R == NULL)
    {
        printf("\nUnable to process transaction data.\n");

        free(L);
        free(R);

        return;
    }


    for(i = 0; i < n1; i++)
    {
        L[i] = transactions[left + i];
    }


    for(j = 0; j < n2; j++)
    {
        R[j] = transactions[mid + 1 + j];
    }


    i = 0;
    j = 0;
    k = left;


    while(i < n1 && j < n2)
    {
        mergeComparisons++;

        if(L[i].amount <= R[j].amount)
        {
            transactions[k] = L[i];
            i++;
        }
        else
        {
            transactions[k] = R[j];
            j++;
        }

        k++;
    }


    while(i < n1)
    {
        transactions[k] = L[i];

        i++;
        k++;
    }


    while(j < n2)
    {
        transactions[k] = R[j];

        j++;
        k++;
    }


    free(L);
    free(R);
}


/* ============================================================
   MERGE SORT
   ============================================================ */

void mergeSort(Transaction transactions[],
               int left,
               int right)
{
    int mid;

    if(left < right)
    {
        mid = left + (right - left) / 2;

        mergeSort(transactions, left, mid);

        mergeSort(transactions, mid + 1, right);

        merge(transactions, left, mid, right);
    }
}


/* ============================================================
   QUICK SORT PARTITION
   ============================================================ */

int partition(Transaction transactions[],
              int low,
              int high)
{
    double pivot;

    int i;
    int j;

    Transaction temp;


    pivot = transactions[high].amount;

    i = low - 1;


    for(j = low; j < high; j++)
    {
        quickComparisons++;

        if(transactions[j].amount <= pivot)
        {
            i++;

            temp = transactions[i];

            transactions[i] = transactions[j];

            transactions[j] = temp;
        }
    }


    temp = transactions[i + 1];

    transactions[i + 1] = transactions[high];

    transactions[high] = temp;


    return i + 1;
}


/* ============================================================
   QUICK SORT
   ============================================================ */

void quickSort(Transaction transactions[],
               int low,
               int high)
{
    int pivotIndex;

    if(low < high)
    {
        pivotIndex = partition(transactions,
                               low,
                               high);

        quickSort(transactions,
                  low,
                  pivotIndex - 1);

        quickSort(transactions,
                  pivotIndex + 1,
                  high);
    }
}


/* ============================================================
   SORT BY TRANSACTION ID
   INTERNAL ONLY
   Used before binary search.
   ============================================================ */

void sortByTransactionID(Transaction transactions[],
                         int left,
                         int right)
{
    int mid;

    int i;
    int j;
    int k;

    int n1;
    int n2;

    Transaction *L;
    Transaction *R;


    if(left >= right)
    {
        return;
    }


    mid = left + (right - left) / 2;


    sortByTransactionID(transactions,
                        left,
                        mid);

    sortByTransactionID(transactions,
                        mid + 1,
                        right);


    n1 = mid - left + 1;
    n2 = right - mid;


    L = (Transaction *)malloc(n1 * sizeof(Transaction));

    R = (Transaction *)malloc(n2 * sizeof(Transaction));


    if(L == NULL || R == NULL)
    {
        free(L);
        free(R);

        return;
    }


    for(i = 0; i < n1; i++)
    {
        L[i] = transactions[left + i];
    }


    for(j = 0; j < n2; j++)
    {
        R[j] = transactions[mid + 1 + j];
    }


    i = 0;
    j = 0;
    k = left;


    while(i < n1 && j < n2)
    {
        if(L[i].transactionID <= R[j].transactionID)
        {
            transactions[k] = L[i];

            i++;
        }
        else
        {
            transactions[k] = R[j];

            j++;
        }

        k++;
    }


    while(i < n1)
    {
        transactions[k] = L[i];

        i++;
        k++;
    }


    while(j < n2)
    {
        transactions[k] = R[j];

        j++;
        k++;
    }


    free(L);
    free(R);
}


/* ============================================================
   BINARY SEARCH
   INTERNAL ONLY
   ============================================================ */

int binarySearch(Transaction transactions[],
                 int n,
                 int key)
{
    int low = 0;
    int high = n - 1;

    int mid;


    while(low <= high)
    {
        mid = low + (high - low) / 2;


        if(transactions[mid].transactionID == key)
        {
            return mid;
        }


        if(transactions[mid].transactionID < key)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }


    return -1;
}


/* ============================================================
   SEARCH TRANSACTION
   ============================================================ */

void searchTransaction(Transaction transactions[], int n)
{
    int transactionID;
    int index;


    if(n == 0)
    {
        printf("\nNo transactions available.\n");
        return;
    }


    printf("\n============================================================\n");
    printf("                    SEARCH TRANSACTION\n");
    printf("============================================================\n");


    printf("Enter Transaction ID: ");

    scanf("%d", &transactionID);

    clearInputBuffer();


    /*
       Backend operation:

       1. Sort by transaction ID.
       2. Perform binary search.

       The user does not see these operations.
    */

    sortByTransactionID(transactions,
                        0,
                        n - 1);


    index = binarySearch(transactions,
                         n,
                         transactionID);


    if(index == -1)
    {
        printf("\nNo transaction found with ID %d.\n",
               transactionID);

        return;
    }


    printf("\nTransaction Found\n");

    printf("------------------------------------------------------------\n");

    printf("Transaction ID : %d\n",
           transactions[index].transactionID);

    printf("Customer ID    : %d\n",
           transactions[index].customerID);

    printf("Date           : %s\n",
           transactions[index].date);

    printf("Type           : %s\n",
           transactions[index].type);

    printf("Amount         : Rs. %.2lf\n",
           transactions[index].amount);

    printf("------------------------------------------------------------\n");
}


/* ============================================================
   GENERATE TRANSACTION REPORT
   ============================================================ */

void generateReport(Transaction transactions[], int n)
{
    Transaction *report;


    if(n == 0)
    {
        printf("\nNo transactions available.\n");
        return;
    }


    report = (Transaction *)malloc(
                n * sizeof(Transaction));


    if(report == NULL)
    {
        printf("\nUnable to generate report.\n");
        return;
    }


    copyTransactions(transactions,
                     report,
                     n);


    /*
       Backend automatically chooses the
       appropriate sorting algorithm.
    */

    automaticSort(report, n);


    printf("\n");
    printf("==========================================================================\n");
    printf("                       TRANSACTION REPORT\n");
    printf("==========================================================================\n");

    printf("%-15s %-15s %-15s %-12s %-17s\n",
           "Transaction ID",
           "Customer ID",
           "Date",
           "Type",
           "Amount");

    printf("--------------------------------------------------------------------------\n");


    for(int i = 0; i < n; i++)
    {
        displaySingleTransaction(report[i]);
    }


    printf("--------------------------------------------------------------------------\n");

    printf("Report generated successfully.\n");


    free(report);
}


/* ============================================================
   HIGHEST AND LOWEST TRANSACTION
   ============================================================ */

void highestLowest(Transaction transactions[], int n)
{
    int i;

    int highest = 0;
    int lowest = 0;


    if(n == 0)
    {
        printf("\nNo transactions available.\n");
        return;
    }


    for(i = 1; i < n; i++)
    {
        if(transactions[i].amount >
           transactions[highest].amount)
        {
            highest = i;
        }


        if(transactions[i].amount <
           transactions[lowest].amount)
        {
            lowest = i;
        }
    }


    printf("\n");
    printf("============================================================\n");
    printf("                 TRANSACTION HIGHLIGHTS\n");
    printf("============================================================\n");


    printf("\nHighest Transaction\n");

    printf("Transaction ID : %d\n",
           transactions[highest].transactionID);

    printf("Customer ID    : %d\n",
           transactions[highest].customerID);

    printf("Amount         : Rs. %.2lf\n",
           transactions[highest].amount);


    printf("\nLowest Transaction\n");

    printf("Transaction ID : %d\n",
           transactions[lowest].transactionID);

    printf("Customer ID    : %d\n",
           transactions[lowest].customerID);

    printf("Amount         : Rs. %.2lf\n",
           transactions[lowest].amount);


    printf("============================================================\n");
}


/* ============================================================
   CUSTOMER-SPECIFIC TRANSACTIONS
   ============================================================ */

void customerTransactions(Transaction transactions[], int n)
{
    int customerID;

    int i;

    int found = 0;

    double totalCredit = 0;
    double totalDebit = 0;


    if(n == 0)
    {
        printf("\nNo transactions available.\n");
        return;
    }


    printf("\n============================================================\n");
    printf("                  CUSTOMER TRANSACTIONS\n");
    printf("============================================================\n");


    printf("Enter Customer ID: ");

    scanf("%d", &customerID);

    clearInputBuffer();


    for(i = 0; i < n; i++)
    {
        if(transactions[i].customerID == customerID)
        {
            if(found == 0)
            {
                printf("\n");
                printf("%-15s %-15s %-15s %-12s %-17s\n",
                       "Transaction ID",
                       "Customer ID",
                       "Date",
                       "Type",
                       "Amount");

                printf("--------------------------------------------------------------------------\n");
            }


            displaySingleTransaction(transactions[i]);


            found = 1;


            if(strcmp(transactions[i].type,
                      "Credit") == 0)
            {
                totalCredit += transactions[i].amount;
            }
            else
            {
                totalDebit += transactions[i].amount;
            }
        }
    }


    if(found == 0)
    {
        printf("\nNo transactions found for Customer ID %d.\n",
               customerID);

        return;
    }


    printf("--------------------------------------------------------------------------\n");

    printf("Total Credit : Rs. %.2lf\n",
           totalCredit);

    printf("Total Debit  : Rs. %.2lf\n",
           totalDebit);

    printf("Net Amount   : Rs. %.2lf\n",
           totalCredit - totalDebit);
}


/* ============================================================
   TRANSACTION SUMMARY
   ============================================================ */

void transactionSummary(Transaction transactions[], int n)
{
    int i;

    int creditCount = 0;
    int debitCount = 0;

    double creditAmount = 0;
    double debitAmount = 0;


    if(n == 0)
    {
        printf("\nNo transactions available.\n");
        return;
    }


    for(i = 0; i < n; i++)
    {
        if(strcmp(transactions[i].type,
                  "Credit") == 0)
        {
            creditCount++;

            creditAmount += transactions[i].amount;
        }
        else
        {
            debitCount++;

            debitAmount += transactions[i].amount;
        }
    }


    printf("\n");
    printf("============================================================\n");
    printf("                  TRANSACTION SUMMARY\n");
    printf("============================================================\n");


    printf("\nTotal Transactions : %d\n", n);


    printf("\nCREDIT\n");
    printf("Transactions : %d\n", creditCount);
    printf("Amount       : Rs. %.2lf\n",
           creditAmount);


    printf("\nDEBIT\n");
    printf("Transactions : %d\n", debitCount);
    printf("Amount       : Rs. %.2lf\n",
           debitAmount);


    printf("\nNET BALANCE\n");
    printf("Rs. %.2lf\n",
           creditAmount - debitAmount);


    printf("\n============================================================\n");
}


/* ============================================================
   COPY TRANSACTION ARRAY
   ============================================================ */

void copyTransactions(Transaction source[],
                      Transaction destination[],
                      int n)
{
    int i;

    for(i = 0; i < n; i++)
    {
        destination[i] = source[i];
    }
}
