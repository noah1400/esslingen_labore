import React from 'react'
import SignupForm from '../components/SignupForm';

const Signup = () => {
    return (
        <div className="App">
          <div className='row vh-100 w-100'>
            <div className="col-6 login-backgound">
              <p className='image_link'>Foto von <a href="https://unsplash.com/@lilrohit?utm_source=unsplash&utm_medium=referral&utm_content=creditCopyText">Rohit Choudhari</a> auf <a href="https://unsplash.com/de/fotos/puy-FW4fOJc?utm_source=unsplash&utm_medium=referral&utm_content=creditCopyText">Unsplash</a>
  </p>
            </div>
            <div className="col-6 d-flex align-items-center justify-content-center">
              <SignupForm />
            </div>
          </div>
        </div>
      );
}

export default Signup;