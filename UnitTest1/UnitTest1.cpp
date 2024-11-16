#include "pch.h"
#include "CppUnitTest.h"

#include <fstream>
#include "../lab11.3/FileName.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		vector<string> SearchRoutes(const char* filename, const string& point) {
			ifstream fin(filename);
			vector<string> matchingRoutes;

			if (!fin.is_open()) { // Перевірка на відкриття файлу
				return matchingRoutes; // Повернути порожній вектор, якщо файл не відкрився
			}

			string line;
			while (getline(fin, line)) {
				size_t startIdx = line.find(point + ";");
				size_t endIdx = line.rfind(";" + point);
				if (startIdx == 0 || endIdx != string::npos) {
					matchingRoutes.push_back(line); // Додаємо рядок до результату
				}
			}

			return matchingRoutes; // Повертаємо знайдені маршрути
		}

		TEST_METHOD(Test_SearchRoutes_FindsMatchingRoutes)
		{
			// Arrange
			const char* testFilename = "test_routes.txt";

			// Створюємо тестовий файл із маршрутами
			ofstream fout(testFilename);
			Assert::IsTrue(fout.is_open(), L"Test file could not be created."); // Перевірка, чи файл відкрився
			fout << "Lviv;Kyiv;101\n";
			fout << "Kyiv;Odessa;102\n";
			fout << "Odessa;Lviv;103\n";
			fout.close();

			// Act
			vector<string> result = SearchRoutes(testFilename, "Kyiv");

			// Assert
			Assert::AreEqual(size_t(2), result.size(), L"Incorrect number of matching routes."); // Перевірка розміру
			Assert::AreEqual(string("Lviv;Kyiv;101"), result[0], L"First route is incorrect."); // Перевірка першого маршруту
			Assert::AreEqual(string("Kyiv;Odessa;102"), result[1], L"Second route is incorrect."); // Перевірка другого маршруту

			// Cleanup
			remove(testFilename); // Видаляємо тестовий файл
		}

		TEST_METHOD(Test_SearchRoutes_NoMatchingRoutes)
		{
			// Arrange
			const char* testFilename = "test_routes_empty.txt";

			// Створюємо тестовий файл із маршрутами
			ofstream fout(testFilename);
			Assert::IsTrue(fout.is_open(), L"Test file could not be created."); // Перевірка, чи файл відкрився
			fout << "Lviv;Kyiv;101\n";
			fout << "Odessa;Lviv;103\n";
			fout.close();

			// Act
			vector<string> result = SearchRoutes(testFilename, "NonExistentPoint");

			// Assert
			Assert::AreEqual(size_t(0), result.size(), L"No routes should match the point."); // Перевірка, що немає результатів

			// Cleanup
			remove(testFilename); // Видаляємо тестовий файл
		}
	};
}
