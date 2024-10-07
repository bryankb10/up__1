htmx.defineExtension('custom-validator', {
    onEvent: function(name, evt) {
        if (name === "htmx:validateUrl") {
            let elt = evt.detail.elt;
            let form = elt.closest('form');
            let isValid = true;

            // Validate username
            let username = form.querySelector('input[name="username"]');
            if (username.value.trim() === '') {
                document.getElementById('username-error').style.display = 'inline';
                isValid = false;
            } else {
                document.getElementById('username-error').style.display = 'none';
            }

            // Validate email
            let email = form.querySelector('input[name="email"]');
            if (!/^[^\s@]+@[^\s@]+\.[^\s@]+$/.test(email.value)) {
                document.getElementById('email-error').style.display = 'inline';
                isValid = false;
            } else {
                document.getElementById('email-error').style.display = 'none';
            }

            return isValid;
        }
    }
});
