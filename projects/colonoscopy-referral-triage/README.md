# Colonoscopy Referral Triage

**Original repository:** [RMIT Programming Project 1](https://github.com/rmit-computing-technologies/Programming-Project-1.git)

## Resume summary

Developed a machine-learning capstone project to predict colonoscopy referral-priority categories and support safer clinical triage workflows.

## Technologies

Python, Jupyter Notebook, pandas, NumPy, scikit-learn, LightGBM, XGBoost, TensorFlow/Keras, Matplotlib and Seaborn.

## Engineering focus

- Multiclass prediction of urgent, semi-urgent and routine referral categories
- Data validation, missing-value analysis, feature engineering and leakage prevention
- Comparison of logistic regression, ensemble, boosting and recurrent-neural-network approaches
- Clinical-safety workflows including low-confidence flags, clinical review queues and misclassification analysis
- Flexible input standardisation for dictionary and JSON records
- Deployment-oriented design that supports clinician judgment rather than replacing it

The source README reports LightGBM as the selected model and records accuracy, balanced accuracy, macro F1 and urgent-category recall metrics. These results should be reproduced from the notebooks before being presented as current benchmarks.

## Contribution

The notebook identifies Shaikh Naima Labiba (`s3954789`) as a team member alongside Daniel Rowley, GeonHyeong Do and Julian Mariano. The available archive does not provide a reliable task-by-task contribution breakdown, so this portfolio does not assign individual model components without evidence.

## Running the notebooks

Open `ST-673_organized.ipynb` in Jupyter or Google Colab. Install the dependencies listed in the notebook before execution and provide an approved, non-identifying dataset at the expected path.

The included notebooks have their saved outputs cleared for portfolio publishing. They are documentation and analysis artefacts, not an independently packaged production service.

## Privacy

The original archive contained a patient-level CSV with patient identifiers, dates, clinician names, procedure rooms and clinical fields, plus a sample patient JSON file. Those files were intentionally excluded from this public portfolio snapshot. Do not add them or any identifiable healthcare data without explicit authorization and de-identification review.

## Snapshot provenance

`SOURCE_README.md` is the original README from the uploaded archive. The archive did not include Git metadata, so the original repository remains the source of truth for complete history, branches and attribution.
