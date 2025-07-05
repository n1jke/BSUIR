#ifndef VARIANT_SOLVER_H
#define VARIANT_SOLVER_H

#include <QPlainTextEdit>
#include <QRandomGenerator>
#include <QString>
#include <vector>
#include "hash_map.h"

class VariantSolver {
   public:
    explicit VariantSolver(int size) : hash_map_(size) {}

    void Solve(QPlainTextEdit* memo) {	// random generated nums
        memo->clear();
        memo->appendPlainText("Starting VariantSolver...\n");

        memo->appendPlainText(
            "Step 1: Filling hash map with random integers...");

        const int num_elements = 50;
        const int key_range = 1000;
        const int ten = 10;

        for (int i = 0; i < num_elements; ++i) {
            int key = QRandomGenerator::global()->bounded(key_range);
            int value = key * ten;

            hash_map_.Insert(key, value);
        }

        hash_map_.Print([memo](const std::string& line) {
            memo->appendPlainText(QString::fromStdString(line));
        });

        memo->appendPlainText("Step 2: Removing entries with even keys...");

        std::vector<int> keys_to_remove;

        for (int i = 0; i < hash_map_.GetSize(); ++i) {
            for (size_t j = 0; j < hash_map_.GetBucketSize(i); ++j) {
                int key = hash_map_.GetKeyAt(i, j);
                if (key % 2 == 0) {
                    keys_to_remove.push_back(key);
                }
            }
        }

        for (int key : keys_to_remove) {
            hash_map_.Remove(key);
        }

        hash_map_.Print([memo](const std::string& line) {
            memo->appendPlainText(QString::fromStdString(line));
        });

        memo->appendPlainText("VariantSolver completed successfully.");
    }

   private:
    sml::HashMap<int, int> hash_map_;
};

#endif	// VARIANT_SOLVER_H
