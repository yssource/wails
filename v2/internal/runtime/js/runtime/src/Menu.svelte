<script>

    export let menu;

    console.log({menu})

    export let visible = false;

    function click(id) {
        console.log("MenuItem", id, "pressed")
    }
</script>

{#if visible}
<div class="menu">
    {#if menu.Menu }
        {#each menu.Menu.Items as menuItem}
            {#if menuItem.Type === "Text" }
            <div class="menuitem" on:click={() => click(menuItem.ID)}>
            {#if menuItem.Image }
                <div><img alt="" src="data:image/png;base64,{menuItem.Image}"/></div>
            {/if}
                <div class="menulabel">{menuItem.Label}</div>
            </div>
            {:else if menuItem.Type === "Separator"}
            <div class="separator"><hr/></div>
            {/if}
        {/each}
    {/if}
</div>
{/if}

<style>

    .menu {
        padding: 5px;
        background-color: #0008;
        color: #EEF;
        border-radius: 5px;
        margin-top: 5px;
        position: absolute;
        backdrop-filter: blur(3px) saturate(160%) contrast(45%) brightness(140%);
        border: 1px solid rgb(88,88,88);
        box-shadow: 0 0 1px rgb(146,146,148) inset;
    }

    .menuitem {
        display: flex;
        align-items: center;
        padding: 1px 5px;
    }

    .menuitem:hover {
        display: flex;
        align-items: center;
        background-color: rgb(57,131,223);
        padding: 1px 5px;
        border-radius: 5px;
    }

    .menuitem img {
        padding-right: 5px;
    }

    .separator {
        padding-top: 5px;
        width: 100%;
        padding-bottom: 5px;
    }
    .separator:hover {
        background-color: #0000;
    }

</style>