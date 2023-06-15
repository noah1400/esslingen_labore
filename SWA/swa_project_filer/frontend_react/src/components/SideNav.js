import React, { useContext } from 'react'
import AuthContext from './shared/AuthContext';

const SideNav = () => {
    const { user } = useContext(AuthContext);
    return (
        <div className='col-2 bg-light'>
            <ul className="list-unstyled ms-5 mt-3">
                {user.role==="admin" && <li className='py-2 fw-normal'><a className='text-dark link-underline-light' href='/manage/users'>Admin Management</a></li>}
                {user.role==="admin" && <li className='py-2 fw-normal'><a className='text-dark link-underline-light' href='/manage/groups'>Group Management</a></li>}
                <li className='py-2 fw-normal'><a className='text-dark link-underline-light' href='/'>My Files</a></li>
            </ul>
        </div>
    );
}

export default SideNav;