// Function to validate the name (assuming it should not be empty)
export function validateName(name) {
    return name.trim().length > 0;
}

// Function to validate the email format
//The function uses a regular expression (regex) to validate the email.

export function validateEmail(email) {
    const re = /^(([^<>()\[\]\\.,;:\s@"]+(\.[^<>()\[\]\\.,;:\s@"]+)*)|(".+"))@(([^<>()[\]\\.,;:\s@"]+\.)+[^<>()[\]\\.,;:\s@"]{2,})$/i;
    return re.test(String(email).toLowerCase());
}

// Function to validate a strong password
export function validatePassword(password) {
    const isLongEnough = password.length >= 8;
    const hasUpperCase = /[A-Z]/.test(password);
    const hasLowerCase = /[a-z]/.test(password);
    const hasNumbers = /\d/.test(password);
    const hasSymbols = /[\W_]/.test(password); // \W matches non-word characters, underscore is considered a word character

    return isLongEnough && hasUpperCase && hasLowerCase && hasNumbers && hasSymbols;
}
