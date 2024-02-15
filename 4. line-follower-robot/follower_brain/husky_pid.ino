// PID constants
double Kp = 0.1;  // Proportional term
double Ki = 0.01; // Integral term
double Kd = 0.05; // Derivative term

// PID variables
double integral = 0;
double lastError = 0;

// Function to calculate PID control signal
double calculatePID(int32_t error) {
    // Proportional term
    double P = Kp * error;

    // Integral term
    integral += error;
    double I = Ki * integral;

    // Derivative term
    double derivative = error - lastError;
    double D = Kd * derivative;

    // Total control signal
    double output = P + I + D;

    // Update last error for next iteration
    lastError = error;

    return output;
}
