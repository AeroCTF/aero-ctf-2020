# Code | Captcha

## Info

> We found a site on which the flag is posted but it is hidden behind a large number of captchas. As they understood, the owner does not like bots and created his own captcha generator. Although I’m not a robot, I can’t get beyond 200. Go through the entire captcha and get a reward flag.
>P.s. Login and password are stored in the session.
>
>[Linck]("https://example.com")

## Run

`sudo docke-compose up` and linck of service

## Short description

> Web page with a captcha, you need to go 200 rounds. Upon passing, a flag will be displayed.

## Solution

> 1. Download a couple of tens (hundreds) captchas and notice that there are 4 types of background background.
>
> 2. We divide the captcha by substrates, and combine them according to the similarity of pixels to get a clean background image.
>
> 3. After receiving 4 basic background substrates, we start playing, download (you can download several at once, because you could notice at the previous stage that the code has not changed within 20 seconds) the captcha image, determine the litter background, subtract the background from the downloaded image litter, then we repaint all black pixels in white, all the rest in black.
>
> 4. As a result, we get black text on a white background, we recognize the image and send the text for verification. 

**[Solve sploit](solve/)**

## Flag

`Aero{27af21fab977b178451a5380fb21b6948c6c5f506fd4b021f017a0d8014ddac3}`
