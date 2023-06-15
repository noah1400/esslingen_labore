package swa.filer.controller;

import org.springframework.http.ResponseEntity;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;

@Controller
@RequestMapping("/api/test")
public class TestController {
    
    @GetMapping("/ping")
    public ResponseEntity<String> ping() {
        System.out.println("ping");
        return ResponseEntity.ok("ping");
    }

}
