#include <iostream>
// Very simple pesos, reais and soles currency sum calculator to US dollars

int main() {
  double pesos, reais, soles, dollars;
  
  // Usage of std::cout and std::cin to output and accept users inputs
  std::cout << "Enter number of Colombian Pesos: ";
  std::cin >> pesos; // One peso is 0.00032 in USD

  std::cout << "Enter number of Brazilian Reais: ";
  std::cin >> reais; // One reais is 0.27 USD

  std::cout << "Enter number of Peruvian Soles: ";
  std::cin >> soles; // One sol is 0.3 USD

  dollars = 0.00032 * pesos + 0.27 * reais + 0.3 * soles;

std::cout << "US Dollars = $" << dollars << "\n";

return 0;
}