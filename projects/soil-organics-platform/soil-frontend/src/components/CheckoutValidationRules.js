//This function validates all Payment details entered by a user
export default function validate(values) {
    let errors = {};
    //Validate email
    if (!values.email) {
      errors.email = 'Email address is required';
    } else if (!/\S+@\S+\.\S+/.test(values.email)) { /* Regex to check email format */
      errors.email = 'Email address is invalid'; 
    }
    //Validate postcode
    if (!values.postcode) {
      errors.postcode = 'Enter a 4 digit postcode';
    }
    else if (!/^[0-9]{4}$/.test(values.postcode)) { /* Regex to check postcode format */
      errors.postcode = 'Postcode must be 4 digits';
    }
    //Validate card number
    if (!values.cardNumber) {
      errors.cardNumber = 'Card number is required';
    } else if (values.cardNumber.length !== 16) {
      errors.password = 'Enter a valid card number'; /* 16 digit card no. */
    }
    //Validate name on card
    if (!values.nameoncard) {
        errors.nameoncard = 'Enter your name exactly as it\'s written on your card';
    }
    //Validate expiry
    /* Regex to check postcode format */
    if (!values.expiry || !(/^(0[1-9]|1[0-2])\/?([0-9]{4}|[0-9]{2})$/).test(values.expiry)) { 
        errors.expiry = 'Enter a valid expiration date'; 
    }

    //Validate CVC
    if (!values.cvc || values.cvc.length !== 3) {
        errors.cvc = 'Enter the CVC or security code on your card';
    }
    return errors;
  };