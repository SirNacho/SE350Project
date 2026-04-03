package dev.sirnacho.se350Project;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

@SpringBootApplication
@RestController
public class se350ProjectApplication {

	public static void main(String[] args) {
		SpringApplication.run(se350ProjectApplication.class, args);
	}

  @GetMapping("/test")
    public String hello(@RequestParam(value = "name", defaultValue = "SE350!!!") String name) {
      return String.format("Hello %s!", name);
    }

}
