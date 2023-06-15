package swa.filer.controller;

import jakarta.servlet.http.HttpServletRequest;
import jakarta.validation.Valid;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpHeaders;
import org.springframework.http.ResponseCookie;
import org.springframework.http.ResponseEntity;
import org.springframework.security.authentication.AuthenticationManager;
import org.springframework.security.authentication.UsernamePasswordAuthenticationToken;
import org.springframework.security.core.Authentication;
import org.springframework.security.core.context.SecurityContextHolder;
import org.springframework.security.crypto.password.PasswordEncoder;
import org.springframework.web.bind.annotation.CrossOrigin;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import swa.filer.exception.TokenRefreshException;
import swa.filer.models.RefreshToken;
import swa.filer.models.User;
import swa.filer.payload.request.LoginRequest;
import swa.filer.payload.request.SignupRequest;
import swa.filer.payload.response.MessageResponse;
import swa.filer.payload.response.UserInfoResponse;
import swa.filer.repository.UserRepository;
import swa.filer.security.jwt.JwtUtils;
import swa.filer.security.services.RefreshTokenService;
import swa.filer.security.services.UserDetailsImpl;

@CrossOrigin(origins = "*", maxAge = 3600)
@RestController
@RequestMapping("/api/auth")
public class AuthController {
    @Autowired 
    AuthenticationManager authenticationManager;

    @Autowired
    UserRepository userRepository;

    // other repositories needed for authentication
    // (signup, signin, signout, etc.)
    // ...

    @Autowired
    PasswordEncoder passwordEncoder;

    @Autowired
    JwtUtils jwtUtils;

    @Autowired
    RefreshTokenService refreshTokenService;

    @PostMapping("/signin")
    public ResponseEntity<?> authenticateUser(@Valid @RequestBody LoginRequest loginRequest) {

        Authentication authentication = authenticationManager.authenticate(
            new UsernamePasswordAuthenticationToken(loginRequest.getEmail(), loginRequest.getPassword()));
    
        SecurityContextHolder.getContext().setAuthentication(authentication);
        
        UserDetailsImpl userDetails = (UserDetailsImpl) authentication.getPrincipal();    
        
        ResponseCookie jwtCookie = jwtUtils.generateJwtCookie(userDetails);

        RefreshToken refreshToken = refreshTokenService.createRefreshToken(userDetails.getId());
        ResponseCookie refreshTokenCookie = jwtUtils.generateRefreshJwtCookie(refreshToken.getToken());

        return ResponseEntity.ok()
             .header(HttpHeaders.SET_COOKIE, jwtCookie.toString())
             .header(HttpHeaders.SET_COOKIE, refreshTokenCookie.toString())
             .body(new UserInfoResponse(userDetails.getId(), 
                                        userDetails.getEmail(), 
                                        userDetails.getFirstName(),
                                        userDetails.getLastName()));
     }

     @PostMapping("/signup")
     public ResponseEntity<?> registerUser(@Valid @RequestBody SignupRequest signUpRequest)
     {
        if  (userRepository.existsByEmail(signUpRequest.getEmail())) {
            return ResponseEntity
                .badRequest()
                .body(new MessageResponse("Error: Email is already in use!"));
        }

        // Create new user's account
        User user = new User(
            signUpRequest.getEmail(),
            passwordEncoder.encode(signUpRequest.getPassword()),
            signUpRequest.getFirstName(),
            signUpRequest.getLastName(),
            "STDT_USER",
            signUpRequest.getDateOfBirth()
        );

        userRepository.save(user);

        return ResponseEntity.ok(new MessageResponse("User registered successfully!"));
     }

     @PostMapping("/signout")
     public ResponseEntity<?> logoutUser() {
        Object principal = SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        if (principal.toString() != "anonymousUser") {
            Long userId = ((UserDetailsImpl) principal).getId();
            refreshTokenService.deleteByUserId(userId);
        }

        ResponseCookie jwtCookie = jwtUtils.getCleanJwtCookie();
        ResponseCookie refreshTokenCookie = jwtUtils.getCleanJwtRefreshCookie();

        return ResponseEntity.ok()
            .header(HttpHeaders.SET_COOKIE, jwtCookie.toString())
            .header(HttpHeaders.SET_COOKIE, refreshTokenCookie.toString())
            .body(new MessageResponse("You have been signed out!"));
     }

     @PostMapping("/refreshtoken")
     public ResponseEntity<?> refreshtoken(HttpServletRequest request) {
        String refreshToken = jwtUtils.getJwtFromCookies(request);

        if ((refreshToken != null) && (refreshToken.length() >  0)) {
            return refreshTokenService.findByToken(refreshToken)
                .map(refreshTokenService::verifyExpiration)
                .map(RefreshToken::getUser)
                .map(user -> {
                    ResponseCookie  jwtCookie = jwtUtils.generateJwtCookie(user);

                    return ResponseEntity.ok()
                        .header(HttpHeaders.SET_COOKIE, jwtCookie.toString())
                        .body(new MessageResponse("Token is refreshed successfully!"));
                })
                .orElseThrow(() -> new TokenRefreshException(refreshToken, "Refresh token is not in database!"));
        }

        return ResponseEntity.badRequest().body(new MessageResponse("Refresh Token is empty!"));
     }
}
