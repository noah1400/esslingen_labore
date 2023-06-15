import React from 'react'
import LoginForm from '../components/LoginForm';

const Login = () => {
    return (
        <div className="App">
          <div className='row vh-100 w-100'>
            <div className="col-6 login-backgound">
              <p className='image_link'>Foto von <a href="https://unsplash.com/@nate_dumlao?utm_source=unsplash&utm_medium=referral&utm_content=creditCopyText">Nathan Dumlao</a> auf <a href="https://unsplash.com/de/fotos/c2Y16tC3yO8?utm_source=unsplash&utm_medium=referral&utm_content=creditCopyText">Unsplash</a></p>
            </div>
            <div className="col-6 d-flex align-items-center justify-content-center">
              <LoginForm />
            </div>
          </div>
        </div>
      );
}

export default Login;