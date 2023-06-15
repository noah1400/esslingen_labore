import React, { useContext, useState, useRef } from 'react';
import { useNavigate } from "react-router-dom";
import AuthContext from "./shared/AuthContext";
import dayjs from "dayjs";

const SignupForm = () => {
  const [firstname, setFirstName] = useState('');
  const [lastname, setLastName] = useState('');
  const [dob, setDob] = useState('');
  const [email, setEmail] = useState('');
  const [password, setPassword] = useState('');
  const passref = useRef(null);
  const { signup } = useContext(AuthContext);
  const navigate = useNavigate();

  const handleSubmit = async (e) => {
    e.preventDefault();
    if (password.length<=6) {
      passref.current.classList.add("is-invalid");
    } else {
      // Add your authentication logic here (e.g., call an API, authenticate with a service, etc.)
      let payload = {
        email: email,
        firstName: firstname,
        lastName: lastname,
        role: "standard",
        dateOfBirth: dayjs(dob).format("DD.MM.YYYY"),
        password: password
      };
      await signup(payload).then((result) => {
        navigate("/signin");
      });
    }
  };

  return (
    <div>
      <p className="mb-0 text-start">Welcome!</p>
      <h2 className="mb-4">Create a new account</h2>
      <form onSubmit={handleSubmit}>
        <div className="mb-3">
          <label htmlFor="firstname" className="form-label text-start w-100">First name</label>
          <input type="text" className="form-control py-2" value={firstname} onChange={(e) => setFirstName(e.target.value)} id="firstname" required/>
        </div>
        <div className="mb-3">
          <label htmlFor="lastname" className="form-label text-start w-100">Last name</label>
          <input type="text" className="form-control py-2" value={lastname} onChange={(e) => setLastName(e.target.value)} id="lastname" required/>
        </div>
        <div className="mb-3">
          <label htmlFor="dob" className="form-label text-start w-100">Date of birth</label>
          <input type="date" className="form-control py-2" value={dob} onChange={(e) => setDob(e.target.value)} id="dob" required/>
        </div>
        <div className="mb-3">
          <label htmlFor="email" className="form-label text-start w-100">Email</label>
          <input type="text" className="form-control py-2" value={email} onChange={(e) => setEmail(e.target.value)} id="email" required/>
        </div>
        <div className="mb-5">
          <label htmlFor="password" className="form-label text-start w-100">Passwort</label>
          <input type="password" className="form-control py-2" value={password} onChange={(e) => setPassword(e.target.value)} id="password" ref={passref} required/>
          <div className="invalid-feedback mt-3 text-start">
            Please enter a password with 6+ digits
          </div>
        </div>
        <button type="submit" className="btn btn-light-blue w-100 py-2">Sign Up</button>
      <div className='d-flex mt-4 justify-content-center'>
        <span>Already have an account? <a href="/signin">Sign In</a></span>
      </div>
      </form>
    </div>
  );
};

export default SignupForm;