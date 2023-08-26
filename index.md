---
# Feel free to add content and custom Front Matter to this file.
# To modify the layout, see https://jekyllrb.com/docs/themes/#overriding-theme-defaults

layout: home
title: "Valentin Kiselev, backend developer"
---

{% include home-en.md %}

<script>
if (
    navigator.language?.toLowerCase() === "ru-ru" || 
    navigator.browserLanguage?.toLowerCase() === "ru-ru" || 
    navigator.systemLanguage?.toLowerCase() === "ru-ru" || 
    navigator.userLanguage?.toLowerCase() == "ru-ru"
) {
    window.location = "/ru";
}
</script>