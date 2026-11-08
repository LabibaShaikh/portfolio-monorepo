# Colonoscopy Referral Triage

**Original repository:** [RMIT Programming Project 1](https://github.com/rmit-computing-technologies/Programming-Project-1.git)

## Overview

RMIT machine-learning capstone investigating multiclass prediction of colonoscopy referral priority: Cat 1 urgent, Cat 2 semi-urgent and Cat 3 routine. It is a university clinical decision-support prototype, not a deployed medical product or replacement for clinician judgment.

## Engineering focus

- Dataset validation, missing-value checks, consistency checks, outlier analysis and leakage prevention
- Comparison of logistic regression, Random Forest, Extra Trees, XGBoost, LightGBM and a GRU-based model
- Evaluation using accuracy, balanced accuracy, macro F1, macro recall and urgent-category recall
- Low-confidence flags, clinical review outputs and misclassification analysis
- Input standardisation for dictionary and JSON records

The source README identifies LightGBM as the selected model and reports benchmark metrics. Reproduce the notebooks before treating those metrics as current results.

## Technologies

Python, Jupyter, pandas, NumPy, scikit-learn, LightGBM, XGBoost, TensorFlow/Keras, Matplotlib and Seaborn.

## Contribution and attribution

The notebook identifies Shaikh Naima Labiba (`s3954789`) as a team member alongside Daniel Rowley, GeonHyeong Do and Julian Mariano. The archive does not provide a reliable task-by-task breakdown, so this portfolio does not claim sole ownership of a specific model or evaluation result.

## Running and validation

Open `ST-673_organized.ipynb` in Jupyter or Google Colab and install its imports in an isolated environment. The portfolio notebooks have saved outputs cleared. No current training run is claimed here.

## Privacy

The source archive contained patient-level healthcare and operational data. The CSV and sample patient JSON were excluded; only notebooks with cleared outputs and documentation are included. Use an approved, de-identified dataset for reproduction.

## Future work

External multi-hospital validation, SHAP explanations, referral-text NLP, a clinician-reviewed dashboard and prospective evaluation would be required before considering operational use.
