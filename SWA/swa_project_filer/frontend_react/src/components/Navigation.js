import React, { useContext } from 'react'
import logo from '../assets/Logo_sqared.svg'
import usersvg from '../assets/user.svg'
import { Dropdown } from 'react-bootstrap';
import AuthContext from "./shared/AuthContext";
import { FontAwesomeIcon } from '@fortawesome/react-fontawesome';
import { faRightFromBracket, faUser } from '@fortawesome/free-solid-svg-icons';

const NavigationComponent = () => {
    
    const { signout } = useContext(AuthContext);
    const logout = async () => {
        await signout();
    };
    return (
        <nav className='navbar navbar-expand-lg navbar-light px-4 border-bottom'>
            <a className='navbar-brand d-flex align-items-center' href="./">
                <img src={logo} height='32px' alt=''/>
                <p className='mb-0 ms-3'>FILESYNC</p>
            </a>

            <ul className='navbar-nav ms-auto me-3'>
                <li className='nav-item'>
                    <Dropdown>
                      <Dropdown.Toggle className="bg-white border-0 p-0" variant='light' id="dropdown-basic">
                        <img src={usersvg} className='rounded-circle p-2 bg-light ms-2' alt='profile'/>
                      </Dropdown.Toggle>

                      <Dropdown.Menu>
                        <Dropdown.Item href="#" onClick={logout}><FontAwesomeIcon icon={faRightFromBracket} color='#253858' /> Logout</Dropdown.Item>
                      </Dropdown.Menu>
                    </Dropdown>
                </li>
            </ul>
        </nav>
    );
}

export default NavigationComponent;