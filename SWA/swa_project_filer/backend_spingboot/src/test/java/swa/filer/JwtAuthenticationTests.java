package swa.filer;

import org.junit.jupiter.api.MethodOrderer;
import org.junit.jupiter.api.Order;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.TestMethodOrder;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.autoconfigure.web.servlet.AutoConfigureMockMvc;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.http.MediaType;
import org.springframework.test.web.servlet.MockMvc;
import org.springframework.test.web.servlet.MvcResult;
import org.springframework.test.web.servlet.request.MockMvcRequestBuilders;

import jakarta.servlet.http.Cookie;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.springframework.test.web.servlet.result.MockMvcResultMatchers.*;

@SpringBootTest
@AutoConfigureMockMvc
@TestMethodOrder(MethodOrderer.OrderAnnotation.class)
public class JwtAuthenticationTests {

    @Autowired
	private MockMvc mockMvc;


    @Test
    @Order(1)
    public void testSignup() throws Exception{
        String requestBody = "{\"email\":\"noscit00@hs-esslingen.de\",\"firstName\":\"Noah\",\"lastName\":\"Scholz\",\"role\":\"standard\",\"dateOfBirth\":\"12.03.2002\",\"password\":\"verySecurePassword\"}";
        String expectedResponseBody = "{\"message\":\"User registered successfully!\"}";

        MvcResult mvcResult = mockMvc.perform(MockMvcRequestBuilders.post("/api/auth/signup")
                .contentType(MediaType.APPLICATION_JSON)
                .content(requestBody))
                .andExpect(status().isOk())
                .andExpect(content().contentType(MediaType.APPLICATION_JSON))
                .andExpect(jsonPath("$.message").value("User registered successfully!"))
                .andReturn();

        String actualResponseBody = mvcResult.getResponse().getContentAsString();
        assertEquals(expectedResponseBody, actualResponseBody);
    }
    
    @Test
    @Order(2)
    public void testShouldReturnSetCookieHeader() throws Exception {
        
        // Create the request body
        String requestBody = "{\"email\":\"noscit00@hs-esslingen.de\",\"password\":\"verySecurePassword\"}";

        // Perform the signin request
        MvcResult result = mockMvc.perform(MockMvcRequestBuilders.post("/api/auth/signin")
                .contentType(MediaType.APPLICATION_JSON)
                .content(requestBody))
                .andExpect(status().isOk())
                .andExpect(content().contentType(MediaType.APPLICATION_JSON))
                .andExpect(jsonPath("$.email").value("noscit00@hs-esslingen.de"))
                .andExpect(jsonPath("$.firstname").value("Noah"))
                .andExpect(jsonPath("$.lastname").value("Scholz"))
                .andReturn();

        Cookie cookie = result.getResponse().getCookie("filer_jwt");

        assertNotNull(cookie);

    }

}
