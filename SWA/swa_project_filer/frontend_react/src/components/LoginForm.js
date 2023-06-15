import React, { useContext, useState, useRef } from 'react';
import { useNavigate } from "react-router-dom";
import AuthContext from "./shared/AuthContext";

const LoginForm = () => {
  const [email, setEmail] = useState('admin@hs-esslingen.de');
  const [password, setPassword] = useState('admin123');
  const { login } = useContext(AuthContext);  
  const inputEl = useRef(null), inputEl1 = useRef(null);

  const handleSubmit = async (e) => {
    e.preventDefault();
    // Add your authentication logic here (e.g., call an API, authenticate with a service, etc.)
    let payload = {
      email: email,
      password: password,
    };
    await login(payload).then((result) => {
      inputEl.current.classList.remove("is-invalid");
      inputEl1.current.classList.remove("is-invalid");
    }).catch((err) => {
      inputEl.current.classList.add("is-invalid");
      inputEl1.current.classList.add("is-invalid");
    });
  };

  return (
    <div>
      <p className="mb-0 text-start">Welcome back!</p>
      <h2 className="mb-4">Log in to your account</h2>
      <form onSubmit={handleSubmit}>
        <div className="mb-3">
          <label htmlFor="email" className="form-label text-start w-100">Email</label>
          <input type="text" className="form-control py-2" value={email} onChange={(e) => setEmail(e.target.value)} id="email" ref={inputEl} required/>
        </div>
        <div className="mb-5">
          <label htmlFor="password" className="form-label text-start w-100">Password</label>
          <input type="password" className="form-control py-2" value={password} onChange={(e) => setPassword(e.target.value)} ref={inputEl1} id="password" required/>
          <div className="invalid-feedback mt-3 text-start">
            Wrong Username/Password
          </div>
        </div>
        <button type="submit" className="btn btn-light-blue w-100 py-2">Sign In</button>
      <div className='d-flex mt-4 justify-content-center'>
        <span>Don't have an account? <a href="/signup">Sign Up</a></span>
      </div>
      </form>
    </div>
  );
};

export default LoginForm;