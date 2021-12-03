
/**
 * @author Eric Tang (https://twitter.com/_e_tang)
 */
var tyokiie = tyokiie || {};

$(document).ready(function(){
    $('span[type="link"]').on('click',function(){
        var url = $(this).attr('url');
        if (tyokiie.click_on_link) {
            tyokiie.click_on_link(url);
        }
        else
            console.log('Link clicked: ' + url);
    });
  });