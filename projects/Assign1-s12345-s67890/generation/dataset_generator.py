import random

# Step 1: Read the Sample Dataset
sample_dataset = []
with open('sampleData200k.txt', 'r') as file:
    for line in file:
        sample_dataset.append(line.strip())  # Assuming each line is a record

  # Step 2: Define Sub-Dataset Sizes
sub_dataset_sizes = [500,1250,6900,20300,50000,100000]  # Define the sizes you want

    # Step 3: Generate Sub-Datasets
for size in sub_dataset_sizes:
    sub_dataset = random.sample(sample_dataset, size)  # Randomly sample 'size' records
 
      # Step 4: Create and Write Sub-Datasets to Separate Files
    with open(f'sampData_{size}.txt', 'w') as file:
        for record in sub_dataset:
            file.write(record + '\n')
