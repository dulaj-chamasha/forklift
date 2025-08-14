#include <WiFi.h>
#include <math.h>

// Define known Access Points (APs) with their SSIDs and positions
const char* apSSIDs[] = {
  "SLT_FIBER_349j6", // Replace with AP1 SSID (e.g., "HomeWiFi1")     {"SLT_FIBER_349j6", 3.30, 6.00},
  "Dialog 4G 721",   // Replace with AP2 SSID (e.g., "HomeWiFi2")     {"Dialog 4G 721", 8.00, 1.00},
  "SLT MOBITEL 4G"   // Replace with AP3 SSID (e.g., "HomeWiFi3")     {"SLT MOBITEL 4G", 1.00, 0.50}
};
const float apPositions[][2] = {
  {0, 0},  // AP1 at (0, 0) meters
  {5, 0},  // AP2 at (5, 0) meters
  {1.5, 5}   // AP3 at (0, 5) meters
};
const int numAPs = 3;

// Path loss model parameters
const float A = -44.18; // Reference RSSI at 1 meter (dBm)
const float n = 3.09;   // Path loss exponent

// Number of RSSI samples per AP
const int numSamples = 5;

// Collect RSSI (basic averaging)
void getRSSI(float* rssiValues) {
  for (int i = 0; i < numAPs; i++) {
    float rssiSum = 0;
    int validSamples = 0;
    
    for (int j = 0; j < numSamples; j++) {
      int n = WiFi.scanNetworks();
      float rssi = -100.0;
      for (int k = 0; k < n; k++) {
        if (String(WiFi.SSID(k)) == String(apSSIDs[i])) {
          rssi = WiFi.RSSI(k);
          rssiSum += rssi;
          validSamples++;
          break;
        }
      }
      delay(20);
    }
    
    rssiValues[i] = validSamples > 0 ? rssiSum / validSamples : -100.0;
  }
}

// Convert RSSI to distance
void rssiToDistance(float* rssi, float* distances) {
  for (int i = 0; i < numAPs; i++) {
    if (rssi[i] <= -100.0) {
      distances[i] = 100.0; // Large distance if no signal
    } else {
      distances[i] = pow(10.0, (A - rssi[i]) / (10.0 * n));
    }
  }
}

// Trilateration function (least squares)
bool trilaterate(float* distances, float* position) {
  float A[2][2] = {{0}};
  float b[2] = {0};
  
  for (int i = 1; i < numAPs; i++) {
    A[i-1][0] = 2 * (apPositions[0][0] - apPositions[i][0]);
    A[i-1][1] = 2 * (apPositions[0][1] - apPositions[i][1]);
    b[i-1] = (distances[0] * distances[0] - distances[i] * distances[i]) +
             (apPositions[i][0] * apPositions[i][0] + apPositions[i][1] * apPositions[i][1]) -
             (apPositions[0][0] * apPositions[0][0] + apPositions[0][1] * apPositions[0][1]);
  }
  
  float det = A[0][0] * A[1][1] - A[0][1] * A[1][0];
  if (fabs(det) < 0.0001) return false;
  
  float invA[2][2];
  invA[0][0] = A[1][1] / det;
  invA[0][1] = -A[0][1] / det;
  invA[1][0] = -A[1][0] / det;
  invA[1][1] = A[0][0] / det;
  
  position[0] = invA[0][0] * b[0] + invA[0][1] * b[1];
  position[1] = invA[1][0] * b[0] + invA[1][1] * b[1];
  
  return true;
}

void setup() {
  Serial.begin(115200);
  delay(1000);
  
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  
  Serial.println("ESP32 Basic Trilateration Started");
}

void loop() {
  float rssi[numAPs];
  float distances[numAPs];
  float position[2] = {0};
  
  getRSSI(rssi);
  rssiToDistance(rssi, distances);
  bool valid = trilaterate(distances, position);
  
  // Send data to MATLAB
  Serial.print("DATA:");
  for (int i = 0; i < numAPs; i++) {
    Serial.print(rssi[i]);
    Serial.print(",");
  }
  Serial.print(position[0]);
  Serial.print(",");
  Serial.print(position[1]);
  Serial.println();
  
  delay(1000);
}