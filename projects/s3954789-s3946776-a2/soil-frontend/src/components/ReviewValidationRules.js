//This function validates all Payment details entered by a user
export default function validate(values) {
    let errors = {};
    //Validate review text
    if (!values.reviewText) {
      errors.reviewText = 'Cannot submit an empty review';
    } else { 
        //Check review text is 100 words or less
        const numWords = values.reviewText.trim().split(/\s+/).length;
        if (numWords > 100) {
            errors.reviewText = 'Review must be 100 words or less.';
        } 
    }
    return errors;
  };