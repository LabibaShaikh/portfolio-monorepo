# Predicting Referral Categories for Colonoscopy Patients Using Machine Learning

## Overview

This project investigates the use of machine learning techniques to predict referral-priority categories for colorectal endoscopy patients from demographic, clinical, procedural, and operational healthcare data.

Developed as part of an RMIT University machine learning capstone project, the study focuses on improving elective colorectal cancer referral prioritization workflows through interpretable and deployment-oriented predictive modeling.

The final solution evaluates multiple machine learning approaches and identifies **LightGBM** as the strongest-performing multiclass classifier for referral category prediction.

---

## Objectives

The primary objectives of this project were to:

- Predict referral priority categories:
  - **Cat 1 — Urgent**
  - **Cat 2 — Semi-Urgent**
  - **Cat 3 — Routine**
- Analyze operational bottlenecks and waiting-time breaches
- Compare traditional, ensemble, and boosting machine learning models
- Improve clinical interpretability and deployment readiness
- Prioritize high recall for urgent patients to minimize under-prioritization risk

---

## Dataset

The dataset contains:

- **1,682 patient-level records**
- **53 variables**
- Clinical and operational data collected between **2010–2024**

### Included Features

- Demographics
- BMI
- ASA score
- Procedure type
- Referral category
- Screening indicators
- Waiting-time metrics
- Clinical variables

### Data Preparation

The dataset underwent:

- Missing-value assessment
- Duplicate validation
- Consistency checking
- Outlier analysis
- Feature engineering
- Leakage prevention

---

## Exploratory Data Analysis (EDA)

Key findings from the EDA include:

- Waiting times were strongly right-skewed
- Cat 2 patients represented the primary operational bottleneck
- Referral category strongly influenced waiting times
- BMI demonstrated minimal standalone predictive power
- Demographic variables alone were weak predictors
- Ensemble tree-based methods were better suited to the dataset structure

### Visual Analysis Included

- Correlation matrices
- Distribution plots
- Boxplots
- Waiting-time analysis
- Breach-rate analysis
- Feature interaction analysis

---

## Machine Learning Models

The following models were implemented and evaluated:

- Logistic Regression
- Random Forest
- Extra Trees
- XGBoost
- LightGBM
- GRU-based Recurrent Neural Network

---

## Final Selected Model

### LightGBM

### Final Model Performance

| Metric | Score |
|---|---|
| Accuracy | 0.9377 |
| Balanced Accuracy | 0.8791 |
| Macro F1 Score | 0.8990 |
| Macro Recall | 0.8791 |
| Cat 1 Recall | 0.9727 |
| Cat 1 Precision | 0.9554 |

---

## Key Features

### Clinical Safety Enhancements

The project includes deployment-oriented clinical safety workflows such as:

- Clinical review flags
- Low-confidence prediction detection
- Misclassified patient analysis
- Doctor-facing review tables
- Safety-aware triage logic

### Dynamic Input Standardisation

The pipeline supports:

- Dictionary-based predictions
- JSON-based predictions
- Dynamic column-name mapping
- Flexible external dataset compatibility

### Example Supported Mappings

| External Column | Standardised Feature |
|---|---|
| `SEX` | `gender` |
| `procedure_name` | `procedure_type` |
| `age years` | `age_yrs` |
| `asa score` | `asa_score` |

---

## Technologies Used

### Languages

- Python

### Libraries

- pandas
- numpy
- scikit-learn
- LightGBM
- XGBoost
- matplotlib
- seaborn
- tensorflow / keras

### Development Environment

- Jupyter Notebook
- Google Colab

---

## Repository Structure

```bash
├── notebooks/
│   └── ST-673.ipynb
│
├── report/
│   └── ST673_ML_Report.docx
│
├── data/
│   └── endoscopy_patients.csv
│
├── images/
│   └── figures_and_visualisations/
│
└── README.md
```

## Example Pipeline

The simplified workflow below shows how the final model can process a new patient record using the same feature structure developed during training.

```python
# Example patient input

patient_data = {
    "age_yrs": 67,
    "gender": 1,
    "asa_score": 3,
    "procedure_type": "Colonoscopy",
    "bmi": 28.4
}

# Convert input into model-ready format
patient_df = pd.DataFrame([patient_data])

# Apply preprocessing and prediction pipeline
prediction = final_model.predict(patient_df)
prediction_probability = final_model.predict_proba(patient_df)

print("Predicted referral category:", prediction[0])
print("Prediction confidence:", prediction_probability.max())
```

## Clinical Significance

This project demonstrates how machine learning can support healthcare prioritization systems by:

- Reducing waiting-time inefficiencies
- Improving urgent patient identification
- Supporting clinician decision-making
- Enhancing operational visibility
- Providing interpretable triage assistance

The model is intended as a **clinical decision-support tool** and not as a replacement for clinician judgment.

---

## Future Work

Potential future improvements include:

- External multi-hospital validation
- SHAP explainability integration
- NLP-based referral text analysis
- Dashboard deployment
- Real-time hospital workflow integration
- Prospective clinical evaluation

---

## Limitations

Several limitations should be acknowledged:

- The dataset originates from a single healthcare environment and has not undergone external validation.
- Some clinically relevant variables may not have been available at referral time.
- Referral priority prediction is not equivalent to colorectal cancer diagnosis prediction.
- Model behavior may vary across hospitals, healthcare systems, or patient populations.
- Dynamic input standardization improves flexibility but cannot fully compensate for inconsistent external data quality.
- The model is intended to support clinicians rather than replace clinical judgment.

---

## Deployment Readiness

The project was extended beyond traditional experimentation by incorporating deployment-oriented workflows and safety-aware prediction logic.

### Included Deployment Features

- Dynamic external input standardization
- JSON and dictionary-based prediction support
- Doctor-facing review outputs
- Clinical safety flags
- Misclassified patient analysis
- Confidence-based review recommendations

### Deployment Workflow

```text
External Dataset / JSON / Dictionary
↓
Dynamic Column Standardization
↓
Preprocessing Pipeline
↓
LightGBM Prediction
↓
Confidence Score + Safety Flags
↓
Doctor Review Table
↓
Clinical Decision Support
```

---

## Authors

| Name | Student Number |
|---|---|
| Geonhyeong Do | sXXXXXXX |
| Julian Mariano | sXXXXXXX |
| Shaikh Naima Labiba | s3954789 |
| Daniel Rowley | sXXXXXXX |

---

## Academic Information

| Field | Details |
|---|---|
| Institution | RMIT University |
| Course | Machine Learning |
| Project Code | P000673CSITCP |
| Sponsor | Sonika Tyagi |
| Academic Supervisor | Sunita Verma |

---
