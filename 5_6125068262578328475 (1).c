#include <stdio.h>
#include <string.h>

#define MAX_DOCTORS 100
#define MAX_PATIENTS 100
#define MAX_APPOINTMENTS 100
#define MAX_TESTS 10

// Doctor, Patient, Appointment structures
struct Doctor {
    char name[100];
    char specialization[50];
    int experience;
};

struct Patient {
    char name[100];
    int age;
    char disease[100];
    float consultation_fee;
    float total_test_cost;
    float stay_cost;
    int stay_days;
};

struct Appointment {
    struct Patient patient;
    char doctor_name[100];
    char appointment_date[11]; // Format: DD/MM/YYYY
};

// Test structure
struct Test {
    char name[100];
    float cost;
};

// Arrays to hold records
struct Doctor doctors[MAX_DOCTORS];
struct Patient patients[MAX_PATIENTS];
struct Appointment appointments[MAX_APPOINTMENTS];
struct Test available_tests[MAX_TESTS] = {
    {"Blood Test", 500},
    {"X-Ray", 700},
    {"MRI Scan", 5000},
    {"CT Scan", 3000},
    {"ECG", 800},
    {"Urine Test", 300},
    {"Sugar Test", 400},
    {"Thyroid Test", 600}
};

int doctor_count = 0, patient_count = 0, appointment_count = 0;

// Function prototypes
void addDoctor();
void addPatient();
void viewDoctors();
void viewPatients();
void scheduleAppointment();
void viewAppointments();
void assignTests();
void generateBill();
void saveData();
void loadData();

// Main function
int main() {
    int choice;
    loadData();
    while(1) {
        printf("\nWelcome to the Hospital Management System\n");
        printf("1. Manage Doctors\n");
        printf("2. Manage Patients\n");
        printf("3. Appointment System\n");
        printf("4. Test Management\n");
        printf("5. Billing System\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                printf("1. Add Doctor\n2. View Doctors\n");
                printf("Enter your choice: ");
                scanf("%d", &choice);
                if (choice == 1) {
                    addDoctor();
                } else {
                    viewDoctors();
                }
                break;
            case 2:
                printf("1. Add Patient\n2. View Patients\n");
                printf("Enter your choice: ");
                scanf("%d", &choice);
                if (choice == 1) {
                    addPatient();
                } else {
                    viewPatients();
                }
                break;
            case 3:
                printf("1. Schedule Appointment\n2. View Appointments\n");
                printf("Enter your choice: ");
                scanf("%d", &choice);
                if (choice == 1) {
                    scheduleAppointment();
                } else {
                    viewAppointments();
                }
                break;
            case 4:
                printf("1. Assign Tests\n");
                printf("Enter your choice: ");
                scanf("%d", &choice);
                if (choice == 1) {
                    assignTests();
                }
                break;
            case 5:
                printf("1. Generate Bill\n");
                printf("Enter your choice: ");
                scanf("%d", &choice);
                if (choice == 1) {
                    generateBill();
                }
                break;
            case 6:
                saveData();
                printf("Exiting... Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice, try again!\n");
        }
    }
    return 0;
}

// Function to save data to file
void saveData() {
    FILE *file = fopen("hospital_data.dat", "wb");
    if (!file) {
        printf("Error saving data!\n");
        return;
    }
    fwrite(&doctor_count, sizeof(int), 1, file);
    fwrite(doctors, sizeof(struct Doctor), doctor_count, file);
    fwrite(&patient_count, sizeof(int), 1, file);
    fwrite(patients, sizeof(struct Patient), patient_count, file);
    fwrite(&appointment_count, sizeof(int), 1, file);
    fwrite(appointments, sizeof(struct Appointment), appointment_count, file);
    fclose(file);
}

// Function to load data from file
void loadData() {
    FILE *file = fopen("hospital_data.dat", "rb");
    if (!file) return;  // No previous data found, continue with empty lists
    fread(&doctor_count, sizeof(int), 1, file);
    fread(doctors, sizeof(struct Doctor), doctor_count, file);
    fread(&patient_count, sizeof(int), 1, file);
    fread(patients, sizeof(struct Patient), patient_count, file);
    fread(&appointment_count, sizeof(int), 1, file);
    fread(appointments, sizeof(struct Appointment), appointment_count, file);
    fclose(file);
}

// Function to add a doctor
void addDoctor() {
    if (doctor_count >= MAX_DOCTORS) {
        printf("Cannot add more doctors.\n");
        return;
    }
    printf("Enter Doctor Name: ");
    scanf(" %[^\n]", doctors[doctor_count].name);
    printf("Enter Specialization: ");
    scanf(" %[^\n]", doctors[doctor_count].specialization);
    printf("Enter Experience (years): ");
    scanf("%d", &doctors[doctor_count].experience);
    doctor_count++;
    printf("Doctor added successfully!\n");
}

// Function to add a patient
void addPatient() {
    if (patient_count >= MAX_PATIENTS) {
        printf("Cannot add more patients.\n");
        return;
    }
    printf("Enter Patient Name: ");
    scanf(" %[^\n]", patients[patient_count].name);
    printf("Enter Age: ");
    scanf("%d", &patients[patient_count].age);
    printf("Enter Disease: ");
    scanf(" %[^\n]", patients[patient_count].disease);
    patients[patient_count].consultation_fee = 1000; // Default consultation fee
    patients[patient_count].total_test_cost = 0;
    patients[patient_count].stay_cost = 0;
    patients[patient_count].stay_days = 0;
    patient_count++;
    printf("Patient added successfully!\n");
}

// Function to view all doctors
void viewDoctors() {
    if (doctor_count == 0) {
        printf("No doctors available.\n");
        return;
    }
    printf("Doctors List:\n");
    for (int i = 0; i < doctor_count; i++) {
        printf("%d. Dr. %s | Specialization: %s | Experience: %d Years\n", 
            i+1, doctors[i].name, doctors[i].specialization, doctors[i].experience);
    }
}

// Function to view all patients
void viewPatients() {
    if (patient_count == 0) {
        printf("No patients available.\n");
        return;
    }
    printf("Patients List:\n");
    for (int i = 0; i < patient_count; i++) {
        printf("%d. %s | Age: %d | Disease: %s\n", 
            i+1, patients[i].name, patients[i].age, patients[i].disease);
    }
}

// Function to schedule an appointment
void scheduleAppointment() {
    if (appointment_count >= MAX_APPOINTMENTS) {
        printf("Cannot schedule more appointments.\n");
        return;
    }

    // Input patient name
    char patient_name[100];
    printf("Enter Patient Name: ");
    scanf(" %[^\n]", patient_name);

    // Find the patient
    int patient_index = -1;
    for (int i = 0; i < patient_count; i++) {
        if (strcmp(patients[i].name, patient_name) == 0) {
            patient_index = i;
            break;
        }
    }
    if (patient_index == -1) {
        printf("Patient not found.\n");
        return;
    }

    // Input appointment details
    printf("Enter Appointment Date (DD/MM/YYYY): ");
    scanf(" %[^\n]", appointments[appointment_count].appointment_date);

    printf("Available Doctors:\n");
    viewDoctors();

    printf("Assign Doctor (Enter Doctor Name): ");
    scanf(" %[^\n]", appointments[appointment_count].doctor_name);

    // Store appointment
    appointments[appointment_count].patient = patients[patient_index];
    appointment_count++;
    printf("Appointment scheduled successfully!\n");
}

// Function to view all scheduled appointments
void viewAppointments() {
    if (appointment_count == 0) {
        printf("No appointments scheduled.\n");
        return;
    }
    printf("Scheduled Appointments:\n");
    for (int i = 0; i < appointment_count; i++) {
        printf("Patient: %s | Doctor: %s | Date: %s\n", 
            appointments[i].patient.name, appointments[i].doctor_name, appointments[i].appointment_date);
    }
}

// Function to assign tests to a patient
void assignTests() {
    char patient_name[100];
    printf("Enter Patient Name: ");
    scanf(" %[^\n]", patient_name);

    // Find the patient
    int patient_index = -1;
    for (int i = 0; i < patient_count; i++) {
        if (strcmp(patients[i].name, patient_name) == 0) {
            patient_index = i;
            break;
        }
    }
    if (patient_index == -1) {
        printf("Patient not found.\n");
        return;
    }

    printf("Available Tests:\n");
    for (int i = 0; i < MAX_TESTS; i++) {
        printf("%d. %s - Rs %.2f\n", i+1, available_tests[i].name, available_tests[i].cost);
    }

    int test_choice;
    char another_test = 'y';
    while (another_test == 'y') {
        printf("Enter Test number to assign: ");
        scanf("%d", &test_choice);
        if (test_choice >= 1 && test_choice <= MAX_TESTS) {
            patients[patient_index].total_test_cost += available_tests[test_choice-1].cost;
            printf("Test assigned: %s\n", available_tests[test_choice-1].name);
        } else {
            printf("Invalid test number!\n");
        }
        printf("Assign another test? (y/n): ");
        scanf(" %c", &another_test);
    }
    printf("Tests assigned successfully!\n");
}

// Function to generate final bill for a patient
void generateBill() {
    char patient_name[100];
    printf("Enter Patient Name for Billing: ");
    scanf(" %[^\n]", patient_name);

    // Find the patient
    int patient_index = -1;
    for (int i = 0; i < patient_count; i++) {
        if (strcmp(patients[i].name, patient_name) == 0) {
            patient_index = i;
            break;
        }
    }
    if (patient_index == -1) {
        printf("Patient not found.\n");
        return;
    }

    // Input stay days
    printf("Enter Number of Days for Hospital Stay: ");
    scanf("%d", &patients[patient_index].stay_days);
    patients[patient_index].stay_cost = patients[patient_index].stay_days * 400; // Rs 400 per day

    // Calculate total bill
    float total_bill = patients[patient_index].consultation_fee + 
                    patients[patient_index].total_test_cost + 
                    patients[patient_index].stay_cost;

    printf("\nFinal Bill for %s:\n", patients[patient_index].name);
    printf("Consultation Fee: Rs %.2f\n", patients[patient_index].consultation_fee);
    printf("Tests Cost: Rs %.2f\n", patients[patient_index].total_test_cost);
    printf("Hospital Stay Charges: Rs %.2f\n", patients[patient_index].stay_cost);
    printf("--------------------------------------\n");
    printf("Total Bill: Rs %.2f\n", total_bill);
}
